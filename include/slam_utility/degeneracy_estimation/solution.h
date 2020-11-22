/**
 * @file solution.h
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-11-22
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef SLAM_UTILITY_DEGENERACY_ESTIMATION_SOLUTION_H_
#define SLAM_UTILITY_DEGENERACY_ESTIMATION_SOLUTION_H_

#include <eigen3/Eigen/Eigenvalues>

#include <slam_utility/degeneracy_estimation/types.h>

namespace slam_utility
{
namespace degeneracy_estimation
{
/**
 * @brief implemetation of the degeneracy of state estimation problem
 *
 * @cite{STRIPACK,
 *     author="Ji Zhang, Michael Kaess, and Sanjiv Singh",
 *     title="{On Degeneracy of Optimization-based State Estimation Problems}",
 *     journal="ICRA",
 *     year="2016"}.
 */
class Solution
{
public:
    /**
     * @brief define parameters, e.g. max iteration, eigen_threshhold, etc.
     *
     */
    struct Parameters
    {
        size_t max_iteration   = 100;
        double eigen_threshold = 1e-3;

        // @todo (yanwei) define more parameters

        /**
         * @brief Construct a new Parameters object
         *
         */
        Parameters()
        {
        }
    };

    /**
     * @brief Construct a new Solution object
     *
     * @param params solution parameters
     */
    Solution(const Parameters& params = Parameters()) : params_(params)
    {
    }

    /**
     * @brief Algorithm: Nonlinear Solver with Solution Remapping
     *
     * @param f nonlinear function that support linearization
     * @param xp predicted solution
     * @return VectorXd updated solution
     */
    VectorXd run(NonlinearFunctionBaseT::Ptr f, const VectorXd& xp) const;

private:
    /**
     * @brief
     *
     * @param iteration current iteration
     * @return true
     * @return false
     */
    bool checkConvergency(const size_t iteration) const;

    Parameters params_;
};  // Solution

}  // namespace degeneracy_estimation
}  // namespace slam_utility

#endif  // SLAM_UTILITY_DEGENERACY_ESTIMATION_SOLUTION_H_