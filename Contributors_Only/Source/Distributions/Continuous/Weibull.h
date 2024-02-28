#ifndef DF_WEIBULL_H
#define DF_WEIBULL_H

#include "../distribution.h"

namespace DiceForge {

    /// @brief DiceForge::WEIBULL - A Continuous Probability Distribution (WEIBULL) 
    class Weibull : public Continuous {
        private:
            real_t shift, k, lambda;

        public:
            /// @brief Initializes the Weibull distribution about location x = x0 with scale gamma
            /// @param shift shift parameter of distribution
            /// @param lambda scale factor of the distribution
            /// @param k shape factor of the distribution
            /// @note k > 0, lambda > 0
            Weibull(real_t lambda = 1, real_t k = 1, real_t shift = 0);
        
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            real_t next(real_t r) override final;
        
            /// @brief Returns the theoretical variance of the distribution
            /// @note The variation of a Weibull distribution is undefined
            /// @returns NaN
            real_t variance() const override final;
        
            /// @brief Returns the theoretical expectation value of the distribution
            /// @note The expectation value of a Weibull distribution is undefined
            /// @returns NaN
            real_t expectation() const override final;
        
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns 0
            real_t minValue() const override final;
        
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns positive infinity
            real_t maxValue() const override final;
        
            /// @brief Probability density function of the Weibull distribution
            real_t pdf(real_t x) const override final;
        
            /// @brief Cumulative distribution function of the Weibull distribution
            real_t cdf(real_t x) const override final;
    };
}


#endif
