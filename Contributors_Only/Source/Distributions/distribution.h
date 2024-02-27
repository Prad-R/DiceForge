#ifndef DF_DISTRIBUTION_H
#define DF_DISTRIBUTION_H

#include <memory>
#include "../Generators/generator.h"

namespace DiceForge
{    
    /// @brief DiceForge::Continuous - A generic class for distributions describing continuous random variables
    class Continuous
    {
    public:
        /// @brief Returns the theoretical variance of the distribution
        virtual real_t variance() const = 0;
        /// @brief Returns the theoretical expectation value of the distribution
        virtual real_t expectation() const = 0;
        /// @brief Returns the minimum possible value of the random variable described by the distribution
        virtual real_t minValue() const = 0;
        /// @brief Returns the maximum possible value of the random variable described by the distribution
        virtual real_t maxValue() const = 0;
        /// @brief Probabiliity density function (pdf) of the distribution
        /// @param x location where the pdf is to be evaluated
        virtual real_t pdf(real_t x) const = 0;
        /// @brief Cumulative distribution function (cdf) of the distribution
        /// @param x location where the cdf is to be evaluated [P(X <= x)]
        virtual real_t cdf(real_t x) const = 0;
    };

    /// @brief DiceForge::Discrete - A generic class for distributions describing discrete random variables
    class Discrete
    {
    public:
        /// @brief Returns the theoretical variance of the distribution
        virtual real_t variance() const = 0;
        /// @brief Returns the theoretical expectation value of the distribution
        virtual real_t expectation() const = 0;
        /// @brief Returns the minimum possible value of the random variable described by the distribution
        virtual int_t minValue() const = 0;
        /// @brief Returns the maximum possible value of the random variable described by the distribution
        virtual int_t maxValue() const = 0;
        /// @brief Probabiliity mass function (pmf) of the distribution
        /// @param x location where the pdf is to be evaluated [P(X = x)]
        virtual real_t pmf(int_t x) const = 0;
        /// @brief Cumulative distribution function (cdf) of the distribution
        /// @param x location where the cdf is to be evaluated [P(X <= x)]
        virtual real_t cdf(int_t x) const = 0;
    };
}

#endif