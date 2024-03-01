#include "Bernoulli.h" // Include the abstract classes
#include <iostream>

namespace DiceForge{

    // Constructor
    Bernoulli::Bernoulli(real_t p)
    : p(p)
    {
        if (p < 0 || p > 1) {
            std::cerr << "Error: Invalid probability value for Bernoulli distribution." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    int_t Bernoulli::next(real_t r) 
    {  // Generate a random integer based on the Bernoulli distribution
        if (r>p) { 
            return 0;
        }
        else {
            return 1;
        }
    }
    
    real_t Bernoulli::variance() const{
        // Variance of Bernoulli distribution: p * (1 - p)
        return p * (1 - p);
    }

    real_t Bernoulli::expectation() const {
        // Expectation value of Bernoulli distribution: p
        return p;
    }

    int_t Bernoulli::minValue() const  {
        // Smallest value that can be generated in Bernoulli distribution: 0
        return 0;
    }

    int_t Bernoulli::maxValue() const  {
        // Largest value that can be generated in Bernoulli distribution: 1
        return 1;
    }

    real_t Bernoulli::pmf(int_t x) const  {
        // Probability mass function of Bernoulli distribution
        return x == 1 ? p : 1 - p;
    }

    real_t Bernoulli::cdf(int_t x) const  {
        // Cumulative distribution function of Bernoulli distribution
        return x == 0 ? 1 - p : 1.0;
    }    
};