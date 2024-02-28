#ifndef DF_MAXWELL_H
#define DF_MAXWELL_H

#include "../distribution.h"

namespace DiceForge {
    /// @brief DiceForge::Maxwell - A Continuous Probability Distribution (Maxwell) 
    class Maxwell : public Continuous
    {
        private:
            real_t a;
        public:
            /// @brief Initializes the Maxwell distribution with scale "a"
            /// @param "a" scale factor of the distribution
            /// @note a > 0
            Maxwell(real_t a = 1);
            /// @brief Generates a random number from the Maxwell Distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            real_t next(real_t r);
            /// @brief Returns the theoretical variance of the distribution
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns zero
            real_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns positive infinity
            real_t maxValue() const override final;
            /// @brief Probability density function of the Maxwell distribution
            real_t pdf(real_t x) const override final;
            /// @brief Cumulative distribution function of the Maxwell distribution
            real_t cdf(real_t x) const override final;
    };
}


#endif
