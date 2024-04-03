#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include "Custom.h"
#include "basicfxn.h"

namespace DiceForge {

    CustomDistribution::CustomDistribution(real_t lower, real_t upper, PDF_Function pdf) 
        : lower_limit(lower), upper_limit(upper), pdf_function(pdf)
    {
        // Simpson's rule for CDF calculation
        real_t h = 0.01; // Step size, subject to change 
        real_t sum = 0.0;
        real_t x2 = 0.0;
        real_t cdf = 0;


        for (real_t x = lower_limit; x < upper_limit; x += h) {
            x2=x+h; 
            sum = simpson(pdf_function, x, x2);
            cdf+=sum ;
            cdf_values.push_back(std::make_pair(x, cdf));
        }
    }

    real_t CustomDistribution::next(real_t r)
    {
        // Find the two CDF values between which the random number lies
        real_t prev_cdf = 0.0, next_cdf = 0.0;
        for (const auto& pair : cdf_values) {
            if (pair.second > r) {
                next_cdf = pair.second;
                break;
            }
            prev_cdf = pair.second;
        }
    

        // Linear interpolation to find the corresponding input value
        real_t prev_input = 0.0, next_input = 0.0;
        for (const auto& pair : cdf_values) {
            if (pair.second == prev_cdf)
                prev_input = pair.first;
            else if (pair.second == next_cdf) {
                next_input = pair.first;
                break;
            }
        }

        // Interpolate
        return prev_input + ((r - prev_cdf) / (next_cdf - prev_cdf)) * (next_input - prev_input);
        
    }
        
    real_t CustomDistribution::expectation() const 
    {
        real_t h = 0.0001; // Step size for mean calculation
        real_t sum = 0.0;
        real_t n = (upper_limit - lower_limit) / h;

        for (real_t x = lower_limit; x < upper_limit; x += h) {
            sum += x * pdf_function(x);

        }
        return (sum/n );

    }

    real_t CustomDistribution::variance() const 
    {
        real_t h = 0.0001; // Step size for variance calculation
        real_t sum = 0.0;
        real_t n = (upper_limit - lower_limit) / h;
        real_t mean = expectation(); 

        for (real_t x = lower_limit; x < upper_limit; x += h) {
        real_t diff = x - mean;
        sum += diff * diff * pdf_function(x); // Integrate (x - mean)^2 * f(x)
        }
        return (sum/n);
    }

    real_t CustomDistribution::minValue() const 
    {
        return lower_limit;
    }
    
    real_t CustomDistribution::maxValue() const 
    {
        return upper_limit;
    }

    real_t CustomDistribution::pdf(real_t x) const 
    {
        if (x>upper_limit || x<lower_limit)
            throw std::invalid_argument("Enter a value within the domain of this pdf");

        return (pdf_function(x));
    }

    real_t CustomDistribution::cdf(real_t x) const 
    {   
        if (x>upper_limit || x<lower_limit)
            throw std::invalid_argument("Enter a value within the domain of this pdf");
            
        return (simpson(pdf_function,lower_limit, x));

    }
} // namespace DiceForge


