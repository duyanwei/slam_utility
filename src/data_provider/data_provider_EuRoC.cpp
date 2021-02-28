/**
 * @file data_provider_EuRoC.cpp
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-02-28
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <slam_utility/data_provider/data_provider_EuRoC.h>

namespace slam_utility
{
namespace data_provider
{
////////////////////////////////////////////////////////////////////////////////
DataProviderEuRoC::DataProviderEuRoC(const std::string& dir)
  : DataProviderBase()
{
    loadTimestamp(dir);
    loadImage(dir);
    loadGroundTruth(dir + "/mav0/state_groundtruth_estimate0/data.csv");

    assert(timestamps_.size() == images_.size());
}

////////////////////////////////////////////////////////////////////////////////
DataProviderEuRoC::~DataProviderEuRoC()
{
}

////////////////////////////////////////////////////////////////////////////////
void DataProviderEuRoC::loadTimestamp(const std::string& file)
{
    (void)file;
}

////////////////////////////////////////////////////////////////////////////////
void DataProviderEuRoC::loadImage(const std::string& file)
{
    (void)file;
}

////////////////////////////////////////////////////////////////////////////////
void DataProviderEuRoC::loadGroundTruth(const std::string& file)
{
    std::ifstream handler(file);
    std::string   line;
    std::getline(handler, line);  // skip the first line

    GroundTruth gt;
    while (std::getline(handler, line))
    {
        std::vector<double> values;
        std::istringstream  is(line);
        std::string         str;
        while (std::getline(is, str, ','))
        {
            values.push_back(stod(str));
        }
        gt.timestamp = values.at(0);
        gt.tx        = values.at(1);
        gt.ty        = values.at(2);
        gt.tz        = values.at(3);
        gt.qw        = values.at(4);
        gt.qx        = values.at(5);
        gt.qy        = values.at(6);
        gt.qz        = values.at(7);
        gt.vx        = values.at(8);
        gt.vy        = values.at(9);
        gt.vz        = values.at(10);
        gt.wx        = values.at(11);
        gt.wy        = values.at(12);
        gt.wz        = values.at(13);
        gt.ax        = values.at(14);
        gt.ay        = values.at(15);
        gt.az        = values.at(16);
        gts_.push_back(gt);
    }

    std::cout << "Loaded " << gts_.size() << " ground truth." << std::endl;
}

}  // namespace data_provider

}  // namespace slam_utility
