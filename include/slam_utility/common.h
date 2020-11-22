/**
 * @file common.h
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-11-22
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef SLAM_UTILITY_COMMON_H_
#define SLAM_UTILITY_COMMON_H_

#include <eigen3/Eigen/Geometry>

namespace slam_utility
{
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1>              VectorXd;

}  // namespace slam_utility

#endif  // SLAM_UTILITY_COMMON_H_
