#ifndef DICEFORGE_GIBBS_H
#define DICEFORGE_GIBBS_H

#include "distribution.h"

namespace DiceForge {
    // Gibbs distribution class (derived from Discrete)
    class Gibbs : public DiceForge::Discrete {
        private:
            // Array to store cdf
            real_t *cdf_array = nullptr;
            // Array to store pmf
            real_t *pmf_array = nullptr;
            // Array to store x values (output values)
            int_t *x_array = nullptr;
            // Length of all 3 arrays
            int_t n = 0;
        public:
            // Constructor to initialise the private attributes above
            Gibbs(int_t *x_arr, real_t *func_arr, int len, real_t beta);
            // Destructor to free memory used by the 3 array attributes
            ~Gibbs();
            /* next(r) [Integer] - Returns a random integer following the distribution given a 'r'
             * r is a uniformly distributed unit random variable */
            int_t next(real_t r) override;
            /* variance() [Real] - Returns the variance of the distribution */
            real_t variance() const override;
            /* expectation() [Real] - Returns the expectation value of the distribution */
            real_t expectation() const override;
            /* minValue() [Integer] - Smallest number that can be generated in the distribution */
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
