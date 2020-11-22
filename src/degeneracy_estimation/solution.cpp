/**
 * @file solution.cpp
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-11-22
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <slam_utility/degeneracy_estimation/solution.h>

namespace slam_utility
{
namespace degeneracy_estimation
{
////////////////////////////////////////////////////////////////////////////////
VectorXd Solution::run(NonlinearFunctionBaseT::Ptr f, const VectorXd& xp) const
{
    // linearization
    // @note the author claimed the degenerated direction needs only update once
    auto            result = f->linearize(xp);  // deep copy
    const MatrixXd& A      = result.first;
    const VectorXd& b      = result.second;
    const MatrixXd  AA     = A.transpose() * A;

    // construct Vp, Vu
    Eigen::SelfAdjointEigenSolver<MatrixXd> solver(AA);

    const MatrixXd& Vf = solver.eigenvectors();  // orthonomal matrix
    MatrixXd        Vp(Vf);
    MatrixXd        Vu(Vf);
    bool            degenerated = false;
    {
        const VectorXd& ev = solver.eigenvalues();  // ascending order
        for (size_t i = 0u; i < (size_t)ev.rows(); i++)
        {
            if (ev(i) > params_.eigen_threshold)
            {
                degenerated = true;
                Vp.rightCols(Vf.cols() - i).setZero();
                Vu.leftCols(i).setZero();
                break;
            }
        }
    }

    // @todo (yanwei) use V_u instead of V_p (is it correct???)
    const MatrixXd inv_Vf_times_Vu = Vf.transpose() * Vu;

    // do iterative update
    VectorXd xf(xp);
    size_t   i = 0;
    while (!checkConvergency(i))
    {
        // compute \delta{xu}
        const VectorXd delta_xu = A.llt().solve(b);  // can solve in many ways

        // update xf (use bool to save computation cost)
        xf = xf + (degenerated ? inv_Vf_times_Vu * delta_xu : delta_xu);

        // update A and b
        result = f->linearize(xf);

        i++;
    }
    return xf;
}

////////////////////////////////////////////////////////////////////////////////
bool Solution::checkConvergency(const size_t iteration) const
{
    return iteration >= params_.max_iteration;
}

}  // namespace degeneracy_estimation
}  // namespace slam_utility