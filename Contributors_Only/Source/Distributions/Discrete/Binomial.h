#ifndef DF_NHYPERGEOMETIRC_H
#define DF_NHYPERGEOMETIRC_H

#include "../distribution.h"
#include <vector>

namespace DiceForge {
    /// @brief DiceForge::Binomial - A Discrete Probability Distribution (Binomial Distribution) 
    class Binomial : public Discrete {
        private:
            uint_t n;
            real_t p;
            std::vector<real_t> pmfs;
        public:
            /// @brief Initializes the Binomial Distribution with (n, p)
            /// @param n number of trials 
            /// @param p probability of "success" in each trial
            /// @note 0 <= p <= 1
            Binomial(uint_t n, real_t p);
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            int_t next(real_t r);
            /// @brief Returns the theoretical variance of the distribution
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            int_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            int_t maxValue() const override final;
            /// @brief Probability mass function of the Binomial distribution
            /// @note Here it is the probability of encountering exactly k "success" trials
            real_t pmf(int_t k) const override final;
            /// @brief Cumulative distribution function of the Binomial distribution
            real_t cdf(int_t k) const override final;
    };
}


#endif
