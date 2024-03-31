#ifndef DF_EXPONENTIAL_H
#define DF_EXPONENTIAL_H

#include "distribution.h"

namespace DiceForge {
/// @brief DiceForge::Exponential - A continuous exponential probability distribution
class Exponential : public Continuous {
private:
    real_t k;  // Rate parameter
    real_t x0; // Origin of the distribution
public:
    /**
     * @brief Constructor for Exponential distribution.
     * @param k Rate parameter for the exponential distribution.
     * @param x0 Origin of the distribution.
     */
    Exponential(real_t k, real_t x0 = 0);
    /**
     * @brief Generate a random number from the exponential distribution.
     * @param r Random number in the range [0,1).
     * @returns Random number from the exponential distribution.
     */
    real_t next(real_t r);
    /**
     * @brief Calculate the variance of the distribution.
     * @returns Variance of the exponential distribution.
     */
    real_t variance() const override final;
    /**
     * @brief Calculate the expectation of the distribution.
     * @returns Expectation of the exponential distribution.
     */
    real_t expectation() const override final;
    /**
     * @brief Get the minimum possible value in the distribution.
     * @returns Minimum value of the exponential distribution.
     */
    real_t minValue() const override final;
    /**
     * @brief Get the maximum possible value in the distribution.
     * @returns Maximum value of the exponential distribution.
     */
    real_t maxValue() const override final;
    /**
     * @brief Calculate the probability density function (PDF) of the distribution at a given point x.
     * @param x Point at which to calculate the PDF.
     * @returns PDF value at point x.
     */
    real_t pdf(real_t x) const override final;
    /**
     * @brief Calculate the cumulative distribution function (CDF) of the distribution at a given point x.
     * @param x Point at which to calculate the CDF.
     * @returns CDF value at point x.
     */
    real_t cdf(real_t x) const override final;

    /// @brief Returns the rate parameter of the distribution
    real_t get_k() const;

    /// @brief Returns the origin of the distribution
    real_t get_x0() const;
};
/// @brief Fits the given sample points (x, y=pdf(x)) to an Exponential distribution using linear regression.
/// using Linear Regression after taking log, Gradient Descent as Optimizer, Mean Squared Error as Loss Function
/// @param x list of x coordinates
/// @param y list of corresponding y coordinates where y = pdf(x)
/// @param max_iter maximum iterations to attempt to fit the data (higher to try for better fits)
/// @param epsilon minimum acceptable error tolerance while attempting to fit the data (smaller to try for better fits)
/// @param alpha learning rate for the gradient descent optimizer
/// @returns An Exponential distribution fit to the given sample points
Exponential fitToExponential(const std::vector<real_t> &x, const std::vector<real_t> &y, int max_iter, real_t epsilon, real_t al);
}

#endif
