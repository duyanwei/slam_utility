/**
 * @file test_data_provider_EuRoC.cpp
 * @author duyanwei (duyanwei0702@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-02-28
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <gtest/gtest.h>
#include <slam_utility/data_provider/data_provider_EuRoC.h>

TEST(DataProviderEuRoC, GroundTruth)
{
    const std::string file = "MAV/MH_04_difficult/";

    slam_utility::data_provider::DataProviderEuRoC provider(file);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}