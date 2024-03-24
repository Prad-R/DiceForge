#include "Maxwell.h"
#include <math.h>
//#include "boost/math/special_functions/gamma.hpp"

namespace DiceForge
{            
    Maxwell::Maxwell(real_t a) : a(a)
    {
        if (a<=0)
        {
            throw std::runtime_error("Scaling factor a must be positive");
        }
    }

    real_t Maxwell::next(real_t r1, real_t r2, real_t r3) 
    {
        real_t x1 = (sqrt(-2.0 * log(r1)) * cos(2 * M_PI * r2)) * a;
        real_t x2 = (sqrt(-2.0 * log(r1)) * sin(2 * M_PI * r2)) * a;
        real_t x3 = (sqrt(-2.0 * log(r2)) * cos(2 * M_PI * r3)) * a;
    
        return sqrt(x1*x1 + x2*x2 + x3*x3);
    }

    real_t Maxwell::variance() const 
    {
        return (a * a) * (3 * M_PI - 8)/ M_PI;
    }

    real_t Maxwell::expectation() const 
    {
        return (2 * a) * sqrt(2 / M_PI);
    }

    real_t Maxwell::minValue() const 
    {
        return 0;
    }

    real_t Maxwell::maxValue() const 
    {
        return std::numeric_limits<real_t>().max();
    }

    real_t Maxwell::pdf(real_t x) const 
    {
        return sqrt(2 / M_PI) * x * x * exp(-1 * x * x / 2 * a * a) / a * a * a;
    }

    real_t Maxwell::cdf(real_t x) const 
    {        
        real_t beta = 1/(2*a*a);
        return beta * sqrt(beta)*sqrt(x)*exp(-x*beta)/tgamma(1.5);
        //boost::math::gamma_p(1.5 , x * x/ 2 * a * a);
    } 

    real_t Maxwell::get_a() const
    {
        return a;
    }
} 
