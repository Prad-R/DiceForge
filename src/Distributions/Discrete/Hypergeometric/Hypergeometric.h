#ifndef DF_HYPERGEOMETRIC_H
#define DF_HYPERGEOMETRIC_H

#include "distribution.h"
#include <vector>

namespace DiceForge
{
    /// @brief DiceForge::Discrete - A discrete probability distribution
    /// @details This is the distribution you get when drawing balls without
    /// replacement from an urn with two colors. n is the number of balls you take,
    /// K is the number of red balls in the urn, N is the total number of balls in
    /// the urn, and the return value is the number of red balls you get.
    /// To regenerate samples of the variation this class uses inversion by chop-down
    /// search from start when parameters are small
    class Hypergeometric : public Discrete
    {
    private:
        int32_t N, K, n;
        std::vector<real_t> pmfs;
        std::vector<real_t> cumulative;
        // N - total size of the population
        // K - occurence in the population (successes)
        // n - sample numbers
        // constraints-(n<=N and k<=N and n>=0 and k>=0)
    public:
        /// @brief Constructor for the Hypergeometric distribution
        /// @param N total size of the population
        /// @param K occurence in the population (successes)
        /// @param n sample numbers
        /// @note n<=N, k<=N, n>=0, k>=0
        Hypergeometric(int32_t N, int32_t K, int32_t n); 
        /// @brief Returns the next value of the random variable described by the distribution
        /// @param r A random real number uniformly distributed between 0 and 1
        int_t next(real_t r);        
        /// @brief Returns the theoretical variance of the distribution
        real_t variance() const override;
        /// @brief Returns the theoretical expectation value of the distribution
        real_t expectation() const override;
        /// @brief Returns the minimum possible value of the random variable described by the distribution
        int_t minValue() const override;
        /// @brief Returns the maximum possible value of the random variable described by the distribution
        int_t maxValue() const override;
        /// @brief Probability mass function of the Hypergeometric distribution
        real_t pmf(int_t k) const override;       
        /// @brief Cumulative distribution function of the Hypergeometric distribution 
        real_t cdf(int_t k) const override;
    };
}

#endif