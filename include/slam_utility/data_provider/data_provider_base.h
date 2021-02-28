/**
 * @file data_provider.h
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-02-28
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SLAM_UTILITY_DATA_PROVIDER_DATA_PROVIDER_BASE_H_
#define SLAM_UTILITY_DATA_PROVIDER_DATA_PROVIDER_BASE_H_

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/optional.hpp>

namespace slam_utility
{
namespace data_provider
{
class DataProviderBase
{
public:
    /**
     * @brief define ground truth
     *
     */
    struct GroundTruth
    {
        double timestamp;
        double tx, ty, tz;
        double qw, qx, qy, qz;
        double vx, vy, vz;
        double wx, wy, wz;
        double ax, ay, az;
    };

    /**
     * @brief define image type
     *
     */
    struct Image
    {
        double timetsamp;

        // @todo use cv::Mat or other types
        std::string image;
    };

    /**
     * @brief Construct a new Data Provider object
     *
     */
    DataProviderBase()
    {
    }

    /**
     * @brief Destroy the Data Provider object
     *
     */
    virtual ~DataProviderBase()
    {
    }

    /**
     * @brief Get the Start Timestamp object
     *
     * @return const double
     */
    double getStartTimestamp() const
    {
        return timestamps_.front();
    }

    /**
     * @brief Get the End Timestamp object
     *
     * @return const double
     */
    double getEndTimestamp() const
    {
        return timestamps_.back();
    }

    /**
     * @brief Get the Image Num object
     *
     * @return const size_t
     */
    size_t getImageNum() const
    {
        return timestamps_.size();
    }

    /**
     * @brief Get the Image object
     *
     * @param index
     * @return const Image
     */
    Image getImage(const size_t index) const
    {
        assert(index < images_.size());

        Image image;
        image.timetsamp = timestamps_.at(index);

        // @todo load image data

        return image;
    }

    /**
     * @brief Get the Ground Truth object
     *
     * @param t
     * @param threshold
     * @return boost::optional<GroundTruth>
     */
    boost::optional<GroundTruth>
    getGroundTruth(const double t, const double threshold = 0.05) const
    {
        assert(t >= timestamps_.front());
        assert(t <= timestamps_.back());

        // @todo interpolation
        auto iter = std::lower_bound(gts_.begin(), gts_.end(), t,
                                     [](const GroundTruth& gt, const double t) {
                                         return gt.timestamp < t;
                                     });
        if ((iter == gts_.end()) ||
            (std::fabs(iter->timestamp - t) > threshold))
        {
            return boost::none;
        }
        return *iter;
    }

protected:
    virtual void loadTimestamp(const std::string& file)   = 0;
    virtual void loadImage(const std::string& file)       = 0;
    virtual void loadGroundTruth(const std::string& file) = 0;

    std::vector<double>      timestamps_;
    std::vector<std::string> images_;
    std::vector<GroundTruth> gts_;
};

}  // namespace data_provider

}  // namespace slam_utility

#endif  // SLAM_UTILITY_DATA_PROVIDER_DATA_PROVIDER_BASE_H_
