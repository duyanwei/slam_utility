/**
 * @file summary.h
 * @author Yanwei Du (yanwei.du@gatech.edu)
 * @brief None
 * @version 0.1
 * @date 05-07-2022
 * @copyright Copyright (c) 2022
 */

#ifndef SLAM_UTILITY_STATS_SUMMARY_H_
#define SLAM_UTILITY_STATS_SUMMARY_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <slam_utility/stats/stats.h>

namespace slam_utility
{
namespace stats
{
/**
 * @brief
 *
 */
class TimeSummary
{
public:
    /**
     * @brief
     *
     * @param name
     * @param t
     */
    void update(const std::string& name, double t)
    {
        if (dict_.count(name) == 0)
        {
            dict_[name] = Statsd(name);
        }
        dict_[name].add(t);
    }

    /**
     * @brief
     *
     * @return std::string
     */
    std::string toString() const
    {
        std::stringstream ss;
        ss << "--- TimeSummary ---"
           << "\n";
        for (const auto& d : dict_)
        {
            ss << d.second;
        }
        return ss.str();
    }

    /**
     * @brief
     *
     */
    void report() const
    {
        std::cout << toString() << std::endl;
    }

    /**
     * @brief
     *
     * @param file
     */
    void write(const std::string& file) const
    {
        std::ofstream myfile(file);
        myfile << toString();
        myfile.close();
    }

private:
    std::unordered_map<std::string, Statsd> dict_;
};

}  // namespace stats

}  // namespace slam_utility

#endif  // SLAM_UTILITY_STATS_SUMMARY_H_