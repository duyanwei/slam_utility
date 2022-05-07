/**
 * @file stats.h
 * @author Yanwei Du (duyanwei0702@gmail.com)
 * @brief None
 * @version 0.1
 * @date 05-06-2022
 * @copyright Copyright (c) 2022
 */

#ifndef SLAM_UTILITY_STATS_STATS_H_
#define SLAM_UTILITY_STATS_STATS_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

namespace slam_utility
{
namespace stats
{
/**
 * @brief
 *
 * @tparam T
 */
template <typename T>
class StatsT
{
public:
    using StatsType = StatsT<T>;

    /**
     * @brief Construct a new Stats T object
     *
     */
    StatsT(const std::string& name = "Stats", const std::string& file = "")
      : name_(name)
      , file_(file)
      , count_(0u)
      , sum_(T(0))
      , min_(std::numeric_limits<T>::max())
      , max_(std::numeric_limits<T>::lowest())
      , last_(T(0))
    {
    }

    /**
     * @brief Destroy the Stats T object
     *
     */
    ~StatsT()
    {
        if (!file_.empty())
        {
            std::ofstream myfile(file_);
            myfile << *this;
            myfile.close();
        }
    }

    /**
     * @brief
     *
     * @param v
     */
    void add(const T& v)
    {
        ++count_;
        sum_ += v;
        min_  = std::min(min_, v);
        max_  = std::max(max_, v);
        last_ = v;
    }

    /**
     * @brief
     *
     * @return uint64_t
     */
    uint64_t count() const
    {
        return count_;
    }

    /**
     * @brief
     *
     * @return T
     */
    T sum() const
    {
        return sum_;
    }

    /**
     * @brief
     *
     * @return T
     */
    T min() const
    {
        return min_;
    }

    /**
     * @brief
     *
     * @return T
     */
    T max() const
    {
        return max_;
    }

    /**
     * @brief
     *
     * @return T
     */
    T mean() const
    {
        return count_ > 0u ? sum_ / static_cast<T>(count_) : T(0);
    }

    /**
     * @brief
     *
     * @return T
     */
    T last() const
    {
        return last_;
    }

    /**
     * @brief
     *
     * @param other
     * @return StatsType&
     */
    StatsType& operator+=(const StatsType& other)
    {
        if (other.count() > 0u)
        {
            count_ += other.count();
            sum_ += other.sum();
            min_  = std::min(min_, other.min());
            max_  = std::max(max_, other.max());
            last_ = other.last();
        }
        return *this;
    }

    /**
     * @brief
     *
     * @param lhs
     * @param rhs
     * @return StatsType
     */
    friend StatsType operator+(StatsType& lhs, const StatsType& rhs)
    {
        return lhs += rhs;
    }

    /**
     * @brief
     *
     * @param os
     * @param s
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const StatsType& s)
    {
        os << "--- " << s.name_ << " ---"
           << "\n"
           << "count: " << s.count_ << "\t"
           << "sum: " << s.sum_ << "\t"
           << "mean: " << s.mean() << "\t"
           << "min: " << s.min() << "\t"
           << "max: " << s.max() << std::endl;
        return os;
    }

private:
    std::string name_;
    std::string file_;
    uint64_t    count_;
    T           sum_;
    T           min_;
    T           max_;
    T           last_;
};

using Statsf = StatsT<float>;
using Statsd = StatsT<double>;

}  // namespace stats

}  // namespace slam_utility

#endif  // SLAM_UTILITY_STATS_STATS_H_