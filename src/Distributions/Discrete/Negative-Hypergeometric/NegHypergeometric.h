#ifndef DF_NEGHYPERGEOMETIRC_H
#define DF_NEGHYPERGEOMETIRC_H

#include "distribution.h"

namespace DiceForge {
    /// @brief DiceForge::NegHypergeometric - A Discrete Probability Distribution (Negative Hypergeometric) 
    class NegHypergeometric : public Discrete {
        private:
            uint_t N, K, r;
            real_t* pmfs;
        public:
            /// @brief Initializes the Negative Hypergeometric Distribution with (N, K, r)
            /// @param N size of the population 
            /// @param K number of "success" elements in the population
            /// @param r number of "failure" elements to be encountered before experiment is stopped
            /// @note 0 <= K <= N, 0 <= r <= N - K for a valid distribution
            NegHypergeometric(uint_t N, uint_t K, uint_t r);
            /// @brief Default destuctor
            ~NegHypergeometric();
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
            /// @brief Probabiliity mass function of the Negative hypergeometric distribution
            /// @note Here it is the probability of encountering exactly k "success" elements when the experiment is stopped
            real_t pmf(int_t k) const override final;
            /// @brief Cumulative distribution function of the Negative hypergeometric distribution
            /// @note Here it is the probability of encountering at most k "success" elements when the experiment is stopped
            real_t cdf(int_t k) const override final;
    };
}


#endif
