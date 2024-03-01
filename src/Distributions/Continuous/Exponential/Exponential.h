#ifndef DF_EXPONENTIAL_H
#define DF_EXPONENTIAL_H

#include "distribution.h"

namespace DiceForge
{
    /// @brief DiceForge::Exponential - A continuous exponential probability distribution
    class Exponential : public Continuous
    {
    private:
        real_t k; // Rate parameter
    public:
        /**
         * @brief Constructor for Exponential distribution.
         * @param k Rate parameter for the exponential distribution.
         */
        Exponential(real_t k);
        /**
         * @brief Generate a random number from the exponential distribution.
         * @param r Random number in the range [0,1).
         * @return Random number from the exponential distribution.
         */
        real_t next(real_t r);
        /**
         * @brief Calculate the variance of the distribution.
         * @return Variance of the exponential distribution.
         */
        real_t variance() const override final;
        /**
         * @brief Calculate the expectation of the distribution.
         * @return Expectation of the exponential distribution.
         */
        real_t expectation() const override final;
        /**
         * @brief Get the minimum possible value in the distribution.
         * @return Minimum value of the exponential distribution.
         */
        real_t minValue() const override final;
        /**
         * @brief Get the maximum possible value in the distribution.
         * @return Maximum value of the exponential distribution.
         */
        real_t maxValue() const override final;
        /**
         * @brief Calculate the probability density function (PDF) of the distribution at a given point x.
         * @param x Point at which to calculate the PDF.
         * @return PDF value at point x.
         */
        real_t pdf(real_t x) const override final;
        /**
         * @brief Calculate the cumulative distribution function (CDF) of the distribution at a given point x.
         * @param x Point at which to calculate the CDF.
         * @return CDF value at point x.
         */
        real_t cdf(real_t x) const override final;
    };
}

#endif
