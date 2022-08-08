/**
 * @file undistorter.cpp
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-06-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <slam_utility/camera/undistorter.h>

namespace slam_utility
{
namespace camera
{
////////////////////////////////////////////////////////////////////////////////
Parameters Parameters::loadFromYaml(const std::string& file)
{
    Parameters      p;
    cv::FileStorage fs(file, cv::FileStorage::READ);
    if (!fs.isOpened())
    {
        std::cerr << "failed to open file: " << file << std::endl;
        return p;
    }

    // read extrinsic
    fs["T_BS"] >> p.bTc;
    // read intrinsics
    fs["intrinsics"] >> p.K;
    // // read distortion
    fs["distortion_coefficients"] >> p.D;

    p.camera_model     = (std::string)fs["camera_model"];
    p.distortion_model = (std::string)fs["distortion_model"];
    // read resolution
    {
        cv::FileNodeIterator it    = fs["resolution"].begin();
        int32_t              width = (int32_t)*it;
        ++it;
        int32_t height = (int32_t)*it;
        p.resolution   = cv::Size2i(width, height);
    }
    p.rate = (float)fs["rate_hz"];

    return p;
}

////////////////////////////////////////////////////////////////////////////////
StereoUndistorter::StereoUndistorter(const std::string& left_camera_file,
                                     const std::string& right_camera_file)
  : left_camera_(Parameters::loadFromYaml(left_camera_file))
  , right_camera_(Parameters::loadFromYaml(right_camera_file))
  , rectified_left_camera_(left_camera_)
  , rectified_right_camera_(right_camera_)
{
    // construct extrinsic of left_T_right
    const cv::Mat c1Tc0 = right_camera_.bTc.inv() * left_camera_.bTc;

    std::cout << "c1Tc0: \n"
              << c1Tc0 << "\n"
              << "c0Tc1 \n"
              << c1Tc0.inv() << std::endl;

    // call rectification
    cv::Mat R0, P0, R1, P1, Q;
    cv::stereoRectify(left_camera_.K, left_camera_.D, right_camera_.K,
                      right_camera_.D, left_camera_.resolution,
                      c1Tc0.colRange(0, 3).rowRange(0, 3),
                      c1Tc0.rowRange(0, 3).col(3), R0, R1, P0, P1, Q,
                      cv::CALIB_ZERO_DISPARITY, 1);
    std::cout << "R0: \n"
              << R0 << "\n"
              << "P0:\n"
              << P0 << "\n"
              << "R1:\n"
              << R1 << "\n"
              << "P1:\n"
              << P1 << std::endl;

    // init undistortion map
    cv::initUndistortRectifyMap(
        left_camera_.K, left_camera_.D, R0, P0.colRange(0, 3).rowRange(0, 3),
        left_camera_.resolution, CV_32F, left_M1_, left_M2_);
    cv::initUndistortRectifyMap(
        right_camera_.K, right_camera_.D, R1, P1.colRange(0, 3).rowRange(0, 3),
        right_camera_.resolution, CV_32F, right_M1_, right_M2_);

    // update rectified parameters
    rectified_left_camera_.K = P0.colRange(0, 3).rowRange(0, 3);
    rectified_left_camera_.D.setTo(0);
    rectified_left_camera_.bTc = cv::Mat::eye(cv::Size(4, 4), CV_32F);

    baseline_                 = P1.at<double>(0, 3) / P1.at<double>(0, 0);
    rectified_right_camera_.K = P1.colRange(0, 3).rowRange(0, 3);
    rectified_right_camera_.D.setTo(0);
    rectified_right_camera_.bTc = cv::Mat::eye(cv::Size(4, 4), CV_32F);
    rectified_right_camera_.bTc.at<float>(0, 3) = baseline_;
}

////////////////////////////////////////////////////////////////////////////////
std::pair<cv::Mat, cv::Mat> StereoUndistorter::run(const cv::Mat& left,
                                                   const cv::Mat& right) const
{
    cv::Mat rectified_left, rectified_right;
    cv::remap(left, rectified_left, left_M1_, left_M2_, cv::INTER_LINEAR);
    cv::remap(right, rectified_right, right_M1_, right_M2_, cv::INTER_LINEAR);
    return std::make_pair(rectified_left, rectified_right);
}
}  // namespace camera

}  // namespace slam_utility
