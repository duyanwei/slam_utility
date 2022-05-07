/**
 * @file timer.h
 * @author Yanwei Du (yanwei.du@gatech.edu)
 * @brief None
 * @version 0.1
 * @date 05-07-2022
 * @copyright Copyright (c) 2022
 */

#ifndef SLAM_UTILITY_STATS_TIMER_H_
#define SLAM_UTILITY_STATS_TIMER_H_

#include <chrono>
#include <iostream>
#include <thread>

#include <slam_utility/common.h>

namespace slam_utility
{
namespace stats
{
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief TicTocTimer
 *
 */
class TicTocTimer
{
public:
    using TimePointType = std::chrono::system_clock::time_point;

    /**
     * @brief
     *
     */
    void tic()
    {
        start_ = std::chrono::system_clock::now();
    }

    /**
     * @brief
     *
     * @return double
     */
    double elapsed()
    {
        return elapsedInDuration().count();
    }

    /**
     * @brief
     *
     * @param str
     */
    double toc(const std::string& str = "")
    {
        const double duration = elapsed();
        if (!str.empty())
        {
            std::cout << str << " takes " << duration << " seconds"
                      << std::endl;
        }
        return duration;
    }

private:
    friend class Timer;

    /**
     * @brief
     *
     * @return std::chrono::duration<double>
     */
    std::chrono::duration<double> elapsedInDuration()
    {
        return std::chrono::system_clock::now() - start_;
    }

    TimePointType start_;
};  // class

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Timer
 *
 */
class Timer
{
public:
    /**
     * @brief Construct a new Timer object
     *
     * @param frequency
     */
    Timer(double frequency)
    {
        assert(frequency >= 0.0);  // work in debug mode
        T_ = std::chrono::duration<double>(1.0 / frequency);
    }

    /**
     * @brief
     *
     */
    void start()
    {
        timer_.tic();
    }

    /**
     * @brief
     *
     */
    void stop()
    {
        const std::chrono::duration<double> duration =
            timer_.elapsedInDuration();
        if (duration < T_)
        {
            std::this_thread::sleep_for(T_ - duration);
        }
    }

private:
    TicTocTimer                   timer_;
    std::chrono::duration<double> T_;

};  // class

}  // namespace stats

}  // namespace slam_utility

#endif  // SLAM_UTILITY_STATS_TIMER_H_