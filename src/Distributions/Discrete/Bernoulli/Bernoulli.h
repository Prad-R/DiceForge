#ifndef DF_BERNOULLI_H
#define DF_BERNOULLI_H

#include "distribution.h"

namespace DiceForge {
    /// @brief DiceForge::Bernoulli - A Discrete Probability Distribution (Bernoulli) 
    class Bernoulli : public Discrete {
        private:
            float p;
        public:
            /// @brief Constructor for the Bernoulli Distribution
            /// @param p 
            Bernoulli(real_t p);
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            int_t next(real_t r);
            /// @brief Returns the theoretical variance of the distribution
            /// @returns p(1-p)
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            /// @returns p
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns 0
            int_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns 1
            int_t maxValue() const override final;
            /// @brief Probability mass function of the Bernoulli distribution
            real_t pmf(int_t k) const override final;            
            /// @brief Cumulative distribution function of the Bernoulli distribution
            real_t cdf(int_t k) const override final;
    };
}


#endif


