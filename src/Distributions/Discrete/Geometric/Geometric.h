#ifndef DF_GEOMETRIC_H
#define DF_GEOMETRIC_H

#include "distribution.h"

namespace DiceForge {
    /// @brief DiceForge::Geometric - A Discrete Probability Distribution (Geometric) 
    class Geometric : public Discrete {
        private:
            float p;
        public:
            /// @brief Constructor for the Geometric distribution
            /// @param p probability of "success"
            Geometric(real_t p);
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            int_t next(real_t r);            
            /// @brief Returns the theoretical variance of the distribution
            /// @returns (1-p)/(p^2)
            real_t variance() const override;
            /// @brief Returns the theoretical expectation value of the distribution
            /// @return 1/p
            real_t expectation() const override;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @return 0
            int_t minValue() const override;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @return positive infinity
            int_t maxValue() const override;
            /// @brief Probability mass function of the Geometric distribution
            real_t pmf(int_t k) const override;        
            /// @brief Cumulative distribution function of the Geometric distribution 
            real_t cdf(int_t k) const override;
    };
}


#endif