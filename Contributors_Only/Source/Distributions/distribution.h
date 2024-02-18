#ifndef DF_DISTRIBUTION_H
#define DF_DISTRIBUTION_H

#include <memory>
#include "../Generators/generator.h"

namespace DiceForge
{    
    class Continuous
    {
    public:
        /* next(r) [Real] - Returns a random real following the distribution given a 'r'
        * r is a uniformly distributed unit random variable */
        virtual real_t next(real_t r) = 0;
        /* variance() [Real] - Returns the variance of the distribution */
        virtual real_t variance() = 0;
        /* expectation() [Real] - Returns the expectation value of the distribution */
        virtual real_t expectation() = 0;
        /* minValue() [Real] - Smallest number that can be generated in the distribution */
        virtual real_t minValue() = 0;
        /* maxValue() [Real] - Largest number that can be generated in the distribution */
        virtual real_t maxValue() = 0;
        /* pdf(x) [Real] - Probability density function */
        virtual real_t pdf(real_t x) = 0;
        /* cdf(x) [Real] - Cumulative distribution function */
        virtual real_t cdf(real_t x) = 0;
    };

    class Discrete
    {
    public:
        /* next(r) [Integer] - Returns a random integer following the distribution given a 'r'
        * r is a uniformly distributed random integer */
        virtual int_t next(int_t r) = 0;
        /* variance() [Real] - Returns the variance of the distribution */
        virtual real_t variance() const = 0;
        /* expectation() [Real] - Returns the expectation value of the distribution */
        virtual real_t expectation() const = 0;
        /* minValue() [Integer] - Smallest number that can be generated in the distribution */
        virtual int_t minValue() const = 0;
        /* maxValue() [Integer] - Largest number that can be generated in the distribution */
        virtual int_t maxValue() const = 0;
        /* pdf(x) [Real] - Probability mass function */
        virtual real_t pmf(real_t x) const = 0;
        /* cdf(x) [Real] - Cumulative distribution function */
        virtual real_t cdf(real_t x) const = 0;
    };
}

#endif