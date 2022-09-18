/**
 * @file test_orb_stereo_matching_latency.cpp
 * @author Yanwei Du (yanwei.du@gatech.edu)
 * @brief None
 * @version 0.1
 * @date 09-17-2022
 * @copyright Copyright (c) 2022
 */

#include <slam_utility/common.h>
#include <slam_utility/stats/timer.h>

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

/**
 * @brief Construct a new TEST object
 *
 * @note background, ORB_SLAM2 stereo matching takes more than 2x than
 * ORB_SLAM3, the only difference is ORB2 normalized feature descriptor patch by
 * subtracting the center pixel value, it uses cv::Mat. This test is to validate
 * if the normalization operation causes the delay.
 * As a result, in the example below, the normalization with cv::Mat takes even
 * more than the rest of the operations (>= 2x)
 */
namespace internal
{
double runKernel(const cv::Mat& left, const cv::Mat& right, size_t nf, size_t w,
                 size_t x, size_t y, int l, bool enable_normalization)
{
    slam_utility::stats::TicTocTimer timer;
    timer.tic();
    for (size_t i = 0; i < nf; ++i)
    {
        cv::Mat IL = left.rowRange(y - w, y + w + 1).colRange(x - w, x + w + 1);
        if (enable_normalization)
        {
            IL.convertTo(IL, CV_32F);
            IL = IL -
                 IL.at<float>(w, w) * cv::Mat::ones(IL.rows, IL.cols, CV_32F);
        }

        for (int incR = -l; incR <= l; ++incR)
        {
            cv::Mat IR = right.rowRange(y - w, y + w + 1)
                             .colRange(x - w + incR, x + w + 1 + incR);
            if (enable_normalization)
            {
                IR.convertTo(IR, CV_32F);
                IR = IR - IR.at<float>(w, w) *
                              cv::Mat::ones(IR.rows, IR.cols, CV_32F);
            }
            const float dist = cv::norm(IL, IR, cv::NORM_L1);
            (void)dist;
        }
    }
    return timer.elapsed();
}
}  // namespace internal

TEST(StereoMatching, Latency)
{
    // create two random image
    const int width  = 320;
    const int height = 240;
    cv::Mat   left(height, width, CV_8UC1);
    cv::Mat   right(height, width, CV_8UC1);
    cv::randu(left, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
    cv::randu(right, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));

    const size_t nf = 800;  // number of feature
    const size_t w  = 5;    // half patch size
    const size_t x  = width / 2;
    const size_t y  = height / 2;
    const int    l  = 3;  // sliding window

    const size_t max_iter = 100;
    double       cost1    = 0.0;
    double       cost2    = 0.0;

    bool enable_normalization = true;
    for (size_t iter = 0; iter < max_iter; ++iter)
    {
        cost1 += internal::runKernel(left, right, nf, w, x, y, l,
                                     enable_normalization);
        cost2 += internal::runKernel(left, right, nf, w, x, y, l,
                                     !enable_normalization);
    }

    cost1 /= max_iter;
    cost2 /= max_iter;

    std::cout << "Latency with normalization: " << cost1
              << ", w/o normalization:: " << cost2
              << ", diff: " << std::abs(cost1 - cost2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}