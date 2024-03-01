#ifndef DF_GAUSSIAN_H
#define DF_GAUSSIAN_H

#include "../distribution.h"

namespace DiceForge {
    /// @brief DiceForge::Gaussian - A Continuous Probability Distribution (Gaussian) 
    class Gaussian : public Continuous {
        private:
            real_t mu, sigma;
        public:
            /// @brief Initializes the Gaussian distribution about location x = mu with standard deviation sigma
            /// @param mu mean of the distribution
            /// @param sigma standard deviation of the distribution
            Gaussian(real_t mu = 0, real_t sigma = 1);
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r1 A random real number uniformly distributed between 0 and 1
            /// @param r2 A random real number uniformly distributed between 0 and 1
            real_t next(real_t r1, real_t r2);
            /// @brief Returns the theoretical variance of the distribution
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            /// @returns mean of the distribution
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns negative infinity
            real_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns positive infinity
            real_t maxValue() const override final;
            /// @brief Probability density function of the Gaussian distribution
            real_t pdf(real_t x) const override final;
            /// @brief Cumulative distribution function of the Gaussian distribution
            real_t cdf(real_t x) const override final;
    };
}


#endif

