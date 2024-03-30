#include "Gibbs.h"
#include <algorithm>

namespace DiceForge
{
    Gibbs::Gibbs(int_t x_arr[], real_t func_arr[], int len, real_t beta){
        n = len;
        // Display error if n is not at least 1
        if (n <= 0) {
            throw std::invalid_argument("len must be positive!");
        }
        
        // Sort the pmf in increasing order of x (required for constructing cdf)
        std::pair<int,double> xy_arr[n];
        for (int i = 0; i < n; i++){
            xy_arr[i].first = x_arr[i];
            xy_arr[i].second = func_arr[i];
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

    Gibbs::~Gibbs(){
        // Free memory used by 3 arrays
        free(cdf_array);
        free(pmf_array);
        free(x_array);
    }

    int_t Gibbs::next(real_t r){
        // Binary search for x such that : P(X < x) <= r < P(X <= x)
        return x_array[(std::upper_bound(cdf_array, cdf_array + n, r) - cdf_array)];
    }

    real_t Gibbs::variance() const{
        real_t exp = expectation();
        real_t v = 0;
        // var(X) = sum{ p_i * (x_i - E(X))^2 }
        for (int i = 0; i < n; i++){
            v += pmf_array[i] * (x_array[i] - exp) * (x_array[i] - exp);
        }
        return v;
    }

    real_t Gibbs::expectation() const{
        // E(x) = sum{ p_i * x_i }
        real_t e = 0;
        for (int i = 0; i < n; i++){
            e += pmf_array[i] * x_array[i];
        }
        return e;
    }

    int_t Gibbs::minValue() const{
        // Since x_array is sorted, return first element
        return x_array[0];
    }


    int_t Gibbs::maxValue() const{
        // Since x_array is sorted, return last element
        return x_array[n - 1];
    }


    real_t Gibbs::pmf(int_t x) const{
        // Binary search for x in x_array and return corresponding pmf
        int_t *ptr = std::upper_bound(x_array, x_array + n, x);
        if (ptr == x_array or *(ptr-1) != x){
            return 0;
        }
        return pmf_array[ptr - x_array - 1];
    }


    real_t Gibbs::cdf(int_t x) const{
        // Binary search for x in x_array and return corresponding cdf
        int_t *ptr = std::upper_bound(x_array, x_array + n, x);
        if (ptr == x_array){
            return 0;
        }
        return cdf_array[ptr - x_array - 1];
    }
}