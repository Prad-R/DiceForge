#ifndef DF_GIBBS_H
#define DF_GIBBS_H

#include "distribution.h"
#include <algorithm>

namespace DiceForge {
    // Gibbs distribution class (derived from Discrete)
    class Gibbs : public Discrete {
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
        template <typename RandomAccessIterator1, typename RandomAccessIterator2>
        Gibbs(RandomAccessIterator1 sequence_first, RandomAccessIterator1 sequence_last,
              RandomAccessIterator2 function_first, RandomAccessIterator2 function_last,
              real_t beta){
            // Display error if lengths don't match
            if (sequence_last - sequence_first != function_last - function_first){
                throw std::invalid_argument("Lengths of sequence and function sequence must match!");
            }
            n = sequence_last - sequence_first;
            // Display error if n is not at least 1
            if (n <= 0) {
                throw std::invalid_argument("len must be positive!");
            }

            // Sort the pmf in increasing order of x (required for constructing cdf)
            std::pair<int_t, real_t> xy_arr[n];
            for (int i = 0; i < n; i++){
                xy_arr[i].first = sequence_first[i];
                xy_arr[i].second = function_first[i];
            }
            std::sort(xy_arr, xy_arr + n);

            // Display error if x values are not unique
            for (int i = 1; i < n; i++) {
                if (xy_arr[i].first == xy_arr[i - 1].first) {
                    throw std::invalid_argument("All x values in x_arr must be unique!");
                }
            }

            // Store x_array
            x_array = (int_t*)malloc(n * sizeof(int_t));
            for (int i = 0; i < n; i++){
                x_array[i] = xy_arr[i].first;
            }

            // Store pmf_array and cdf_array (prefix sum array of pmf_array)
            pmf_array = (real_t *)malloc(n * sizeof(real_t));
            cdf_array = (real_t *)malloc(n * sizeof(real_t));
            real_t prev = 0;
            for (int i = 0; i < n; i++){
                pmf_array[i] = exp(- beta * xy_arr[i].second);
                cdf_array[i] = prev + pmf_array[i];
                prev = cdf_array[i];
            }

            // Divide by Z(beta) = cdf_array[n - 1] for normalisation
            for (int i = 0; i < n; i++){
                pmf_array[i] /= cdf_array[n - 1];
                cdf_array[i] /= cdf_array[n - 1];
            }
        }
        // Destructor to free memory used by the 3 array attributes
        ~Gibbs();
        /* next(r) [Integer] - Returns a random integer following the distribution given a 'r'
         * r is a uniformly distributed unit random variable */
        int_t next(real_t r);
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
