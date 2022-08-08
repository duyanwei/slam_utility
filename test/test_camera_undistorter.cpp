/**
 * @file test_camera_undistorter.cpp
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-06-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <slam_utility/camera/undistorter.h>

#include <gtest/gtest.h>
#include <opencv2/highgui.hpp>

std::string g_prefix =
    "/home/duyanwei/duyanwei/github/slam_utility/params/EuRoC/";

TEST(Parameters, ostream)
{
    slam_utility::camera::Parameters p;
    std::cout << p << std::endl;
}

TEST(Parameters, loadFromYaml)
{
    const std::string left_camera_file = g_prefix + "left_camera.yaml";

    slam_utility::camera::Parameters p =
        slam_utility::camera::Parameters::loadFromYaml(left_camera_file);
    std::cout << p << std::endl;
}

TEST(StereoUndistorter, Constructor)
{
    const std::string left_camera_file  = g_prefix + "left_camera.yaml";
    const std::string right_camera_file = g_prefix + "right_camera.yaml";

    slam_utility::camera::StereoUndistorter undistorter(left_camera_file,
                                                        right_camera_file);

    std::cout << "baseline: " << undistorter.getBaseline() << "\n"
              << "rectified left parameters: \n"
              << undistorter.getRectifiedLeftCameraParameters()
              << "rectified right parameters: \n"
              << undistorter.getRectifiedRightCameraParameters() << std::endl;
}

TEST(StereoUndistorter, Run)
{
    const std::string left_camera_file  = g_prefix + "left_camera.yaml";
    const std::string right_camera_file = g_prefix + "right_camera.yaml";

    slam_utility::camera::StereoUndistorter undistorter(left_camera_file,
                                                        right_camera_file);

    cv::Mat left   = cv::imread(g_prefix + "left.png");
    cv::Mat right  = cv::imread(g_prefix + "right.png");
    auto    result = undistorter.run(left, right);

    // show the result
    cv::Mat canvas(left.rows * 2 + 10, left.cols * 2 + 10, left.type());
    left.copyTo(canvas(cv::Range(0, left.rows), cv::Range(0, left.cols)));
    right.copyTo(canvas(cv::Range(0, left.rows),
                        cv::Range(canvas.cols - left.cols, canvas.cols)));
    result.first.copyTo(canvas(cv::Range(canvas.rows - left.rows, canvas.rows),
                               cv::Range(0, left.cols)));
    result.second.copyTo(
        canvas(cv::Range(canvas.rows - left.rows, canvas.rows),
               cv::Range(canvas.cols - left.cols, canvas.cols)));

    cv::namedWindow("compare", CV_WINDOW_NORMAL);
    cv::imshow("compare", canvas);
    cv::waitKey();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}