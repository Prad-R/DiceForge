#include "Exponential.h"

namespace DiceForge
{

    /**
     * @brief Constructor for Exponential distribution.
     * @param k Rate parameter for the exponential distribution.
     */
    Exponential::Exponential(real_t k) : k(k)
    {
        // Check if k is positive
        if (k <= 0)
        {
            throw std::invalid_argument("Rate parameter (k) must be positive");
        }
    }

    /**
     * @brief Generate a random number from the exponential distribution.
     * @param r Random number in the range [0,1).
     * @return Random number from the exponential distribution.
     */
    real_t Exponential::next(real_t r)
    {
        // Inverse transform sampling for exponential distribution
        return -(log(1 - r) / k);
    }

    /**
     * @brief Calculate the variance of the distribution.
     * @return Variance of the exponential distribution.
     */
    real_t Exponential::variance() const
    {
        // Variance formula for exponential distribution
        return 1 / (k * k);
    }

    /**
     * @brief Calculate the expectation of the distribution.
     * @return Expectation of the exponential distribution.
     */
    real_t Exponential::expectation() const
    {
        // Expectation formula for exponential distribution
        return 1 / k;
    }

    /**
     * @brief Get the minimum possible value in the distribution.
     * @return Minimum value of the exponential distribution.
     */
    real_t Exponential::minValue() const
    {
        // Minimum value for exponential distribution
        return std::numeric_limits<real_t>().min();
    }

    /**
     * @brief Get the maximum possible value in the distribution.
     * @return Maximum value of the exponential distribution.
     */
    real_t Exponential::maxValue() const
    {
        // Maximum value for exponential distribution
        return std::numeric_limits<real_t>().max();
    }

    /**
     * @brief Calculate the probability density function (PDF) of the distribution at a given point x.
     * @param x Point at which to calculate the PDF.
     * @return PDF value at point x.
     */
    real_t Exponential::pdf(real_t x) const
    {
        if (x < 0)
        {
            return 0; // PDF is defined only for non-negative x
        }
        else
        {
            // PDF formula for exponential distribution
            // Normalized
            return (exp(-k * x));
        }
    }

    /**
     * @brief Calculate the cumulative distribution function (CDF) of the distribution at a given point x.
     * @param x Point at which to calculate the CDF.
     * @return CDF value at point x.
     */
    real_t Exponential::cdf(real_t x) const
    {
        // CDF formula for exponential distribution
        return (1 - exp(-k * x));
    }

}