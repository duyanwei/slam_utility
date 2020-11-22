/**
 * @file types.h
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-11-22
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef SLAM_UTILITY_DEGENERACY_ESTIMATION_TYPES_H_
#define SLAM_UTILITY_DEGENERACY_ESTIMATION_TYPES_H_

#include <memory>

#include <slam_utility/common.h>

namespace slam_utility
{
namespace degeneracy_estimation
{
/**
 * @brief nonlinear function base class
 */
class NonlinearFunctionBaseT
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    typedef std::shared_ptr<NonlinearFunctionBaseT>       Ptr;
    typedef std::shared_ptr<const NonlinearFunctionBaseT> ConstPtr;

    /**
     * @brief Destroy the Nonlinear Function Base T object
     *
     */
    virtual ~NonlinearFunctionBaseT()
    {
    }

    /**
     * @brief linearize the nonlinear function with state x
     *
     * @param x current state
     * @return const std::pair<MatrixXd, VectorXd>
     */
    virtual const std::pair<MatrixXd, VectorXd>
    linearize(const VectorXd& x) const = 0;

private:
};

}  // namespace degeneracy_estimation
}  // namespace slam_utility

#endif  // SLAM_UTILITY_DEGENERACY_ESTIMATION_TYPES_H_