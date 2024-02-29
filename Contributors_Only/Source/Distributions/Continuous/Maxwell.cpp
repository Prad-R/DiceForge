#include "Maxwell.h"
#include "boost/math/special_functions/gamma.hpp"

namespace DiceForge
{            
    Maxwell::Maxwell(real_t a) : a(a)
    {
        if (a<=0)
        {
            throw std::runtime_error("Scaling factor a must be positive");
        }
    }

    real_t Maxwell::next(real_t r) 
    {
        return a * sqrt(2 * boost::math::gamma_p_inv(1.5 , r));
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
        return boost::math::gamma_p(1.5 , x * x/ 2 * a * a);
    }
} 
