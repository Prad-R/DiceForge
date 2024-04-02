#include "Gibbs.h"

namespace DiceForge
{
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