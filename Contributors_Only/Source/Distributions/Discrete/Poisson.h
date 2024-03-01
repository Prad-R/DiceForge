#ifndef DICEFORGE_POISSON_H
#define DICEFORGE_POISSON_H

#include "../distribution.h"
#include "../../generators.h"

namespace DiceForge {
    
    template <typename T>
    class Poisson : public DiceForge::Discrete {
        private:
            int64_t seed;
            real_t l,sq,lnl,g;
            real_t getran();
            T generator;


        public:
            // Constructor to initialise the private attributes above
            Poisson(real_t, int32_t);

            /* Returns next number */
            int_t next();
            /* variance() [Real] - Returns the variance of the distribution */
            real_t variance() const override;
            /* expectation() [Real] - Returns the expectation value of the distribution */
            real_t expectation() const override;
            /* minValue() [Integer] - Smallest number that can be generated in the distribution  */
            int_t minValue() const override;
            /* maxValue() [Integer] - Largest number that can be generated in the distribution */
            int_t maxValue() const override;
            /* pdf(x) [Real] - Probability mass function */
            real_t pmf(int_t x) const override;
            /* cdf(x) [Real] - Cumulative distribution function */
            real_t cdf(int_t x) const override;
    };
}


#endif
