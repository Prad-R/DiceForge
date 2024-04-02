#include "Geometric.h"
#include <iostream>

namespace DiceForge
{
    // Constructor
    Geometric::Geometric(real_t p)
    : p(p)
    {
        if (p < 0 || p > 1) {
            throw std::invalid_argument("Invalid 'success' probability value for Geometric distribution!");
        }
    }

    int_t Geometric::next(real_t r) 
    {  
        // Cutpoint method of sampling a Geometric distribution
        return floor(log(r)/log(1-p)) + 1;
    }
    
    real_t Geometric::variance() const{
        // Variance of Geometric distribution: (1-p)/(p*p)
        return (1-p)/(p*p);
    }

    real_t Geometric::expectation() const {
        // Expectation value of Geometric distribution: 1/p
        return 1/p;
    }

    int_t Geometric::minValue() const  {
        // Smallest value that can be generated in Geometric distribution: 0
        return 0;
    }

    int_t Geometric::maxValue() const  {
        // Largest value that can be generated in Geometric distribution: infinity
        return std::numeric_limits<int_t>().infinity();
    }

    real_t Geometric::pmf(int_t x) const  {
        // Probability mass function of Geometric distribution
        real_t f =(1-p); 
	    return (1-f)*pow(f,x);
    }

    real_t Geometric::cdf(int_t x) const  {
        // Cumulative distribution function of Geometric distribution
        real_t f = (1-p);
	    int t = (1+floor(x));
        return (1-pow(f,t));
    }       
} 