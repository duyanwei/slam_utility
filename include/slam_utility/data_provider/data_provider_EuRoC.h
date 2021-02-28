/**
 * @file data_provider_euroc.h
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-02-28
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SLAM_UTILITY_DATA_PROVIDER_DATA_PROVIDER_EUROC_H_
#define SLAM_UTILITY_DATA_PROVIDER_DATA_PROVIDER_EUROC_H_

#include <slam_utility/data_provider/data_provider_base.h>

namespace slam_utility
{
namespace data_provider
{
/**
 * @brief this class defines data provider of EuRoC dataset
 *
 * @ref
 * https://projects.asl.ethz.ch/datasets/doku.php?id=kmavvisualinertialdatasets
 *
 */
class DataProviderEuRoC : public DataProviderBase
{
public:
    /**
     * @brief Construct a new Data Provider Eu Ro C object
     *
     * @param dir
     */
    DataProviderEuRoC(const std::string& dir);

    /**
     * @brief Destroy the Data Provider EuRoC object
     *
     */
    virtual ~DataProviderEuRoC();

private:
    /**
     * @brief
     *
     * @param file
     */
    virtual void loadTimestamp(const std::string& file) override;

    /**
     * @brief
     *
     * @param file
     */
    virtual void loadImage(const std::string& file) override;

    /**
     * @brief
     *
     * @param file
     */
    virtual void loadGroundTruth(const std::string& file) override;
};
}  // namespace data_provider
}  // namespace slam_utility

#endif  // SLAM_UTILITY_DATA_PROVIDER_DATA_PROVIDER_EUROC_H_