/**
 * @file test_stats.cpp
 * @author Yanwei Du (yanwei.du@gatech.edu)
 * @brief None
 * @version 0.1
 * @date 05-07-2022
 * @copyright Copyright (c) 2022
 */

#include <gtest/gtest.h>
#include <slam_utility/stats/stats.h>
#include <slam_utility/stats/summary.h>

TEST(Stats, General)
{
    // slam_utility::stats::Statsd s("Statistics", "test.txt");
    slam_utility::stats::Statsd s;

    s.add(1.0);
    s.add(2.0);
    s.add(3.0);

    ASSERT_EQ(3u, s.count());
    ASSERT_EQ(6.0, s.sum());
    ASSERT_EQ(1.0, s.min());
    ASSERT_EQ(3.0, s.max());
    ASSERT_EQ(2.0, s.mean());
    ASSERT_EQ(3.0, s.last());
}

TEST(TimeSummary, General)
{
    // slam_utility::stats::Statsd s("Statistics", "test.txt");
    slam_utility::stats::TimeSummary ts;

    ts.update("preprocessing", 3.1);
    ts.update("preprocessing", 3.3);
    ts.update("preprocessing", 2.9);
    ts.update("tracking", 1.1);
    ts.update("tracking", 1.2);
    ts.update("mapping", 1.8);
    ts.update("mapping", 2.1);

    ts.report();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}