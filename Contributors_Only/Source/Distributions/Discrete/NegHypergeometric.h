#ifndef DF_NHYPERGEOMETIRC_H
#define DF_NHYPERGEOMETIRC_H

#include "../distribution.h"

namespace DiceForge {
    /// @brief DiceForge::NegHypergeometric - A Discrete Probability Distribution (Negative Hypergeometric) 
    class NegHypergeometric : public Discrete {
        private:
            uint_t N, K, r;
        public:
            /// @brief Initializes the Negative Hypergeometric Distribution with (N, K, r)
            /// @param N - size of the population 
            /// @param K - number of "success" elements in the population
            /// @param r - number of "failure" elements to be encountered before experiment is stopped
            /// @note 0 <= K <= N, 0 <= r <= N - K for a valid distribution
            NegHypergeometric(uint_t N, uint_t K, uint_t r);
            int_t next(real_t r) override;
            real_t variance() const override;
            real_t expectation() const override;
            int_t minValue() const override;
            int_t maxValue() const override;
            /// @brief Probability of encountering exactly k "success" elements when the experiment is stopped
            real_t pmf(int_t k) const override;
            /// @brief Probability of encountering at most k "success" elements when the experiment is stopped
            real_t cdf(int_t k) const override;
    };
}


#endif
