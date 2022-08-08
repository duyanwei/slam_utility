/**
 * @file undistorter.h
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-06-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SLAM_UTILITY_CAMERA_UNDISTORTER_H_
#define SLAM_UTILITY_CAMERA_UNDISTORTER_H_

#include <iostream>
#include <string>

#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace slam_utility
{
namespace camera
{
/**
 * @brief
 *
 */
struct Parameters
{
    cv::Mat     bTc;  ///< extrinsic of the left camera(0) w.r.t body
    cv::Mat     D;    ///< distortion
    cv::Mat     K;    ///< intrinsic
    std::string camera_model     = "UNKNOWN";  ///< "pinhole", e.t.c
    std::string distortion_model = "UNKNOWN";  ///< "radial-tangential", e.t.c
    cv::Size2i  resolution       = {0, 0};     ///< image size
    float       rate             = 0;          ///< hz

    /**
     * @brief
     *
     * @param os
     * @param parameters
     * @return sdt::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Parameters& p)
    {
        os << "Parameters \n"
           << "bTc: \n"
           << p.bTc << "\n"
           << "D: " << p.D << "\n"
           << "K: \n"
           << p.K << "\n"
           << "camera_model: " << p.camera_model << "\n"
           << "distortion_model: " << p.distortion_model << "\n"
           << "resolution: " << p.resolution << "\n"
           << "rate: " << p.rate << std::endl;
        return os;
    }

    /**
     * @brief
     *
     * @param file
     * @return Parameters
     */
    static Parameters loadFromYaml(const std::string& file);
};

/**
 * @brief this class defines stereo camera undistorter
 *
 * @details specially it is designed to rectify EuRoC stereo images
 *
 */
class StereoUndistorter
{
public:
    StereoUndistorter(const std::string& left_camera_file,
                      const std::string& right_camera_file);

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return std::pair<cv::Mat, cv::Mat>
     */
    std::pair<cv::Mat, cv::Mat> run(const cv::Mat& left,
                                    const cv::Mat& right) const;

    /**
     * @brief Get the Rectified Left Camera Parameters object
     *
     * @return const Parameters&
     */
    const Parameters& getRectifiedLeftCameraParameters() const
    {
        return rectified_left_camera_;
    }

    /**
     * @brief Get the Rectified Right Camera Parameters object
     *
     * @return const Parameters&
     */
    const Parameters& getRectifiedRightCameraParameters() const
    {
        return rectified_right_camera_;
    }

    /**
     * @brief Get the Baseline object
     *
     * @return float
     */
    float getBaseline() const
    {
        return baseline_;
    }

private:
    Parameters left_camera_;
    Parameters right_camera_;

    Parameters rectified_left_camera_;
    Parameters rectified_right_camera_;

    cv::Mat left_M1_, left_M2_;
    cv::Mat right_M1_, right_M2_;
    float   baseline_;
};

}  // namespace camera

}  // namespace slam_utility

#endif  // SLAM_UTILITY_CAMERA_UNDISTORTER_H_
