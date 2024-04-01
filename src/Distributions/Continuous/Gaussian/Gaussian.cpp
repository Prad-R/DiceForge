#include "Gaussian.h"
#include <vector>

namespace DiceForge
{            
    Gaussian::Gaussian(real_t mu, real_t sigma)
    : mu(mu), sigma(sigma)
    {
        if (sigma < std::numeric_limits<real_t>().epsilon())
        {
            throw std::invalid_argument("sigma must be positive!");
        }
    }

    real_t Gaussian::next(real_t r1, real_t r2) 
    {
        return (sqrt(-2.0 * log(r1)) * cos(2 * M_PI * r2)) * sigma + mu;
    }

    real_t Gaussian::variance() const 
    {
        return sigma * sigma;
    }

    real_t Gaussian::expectation() const 
    {
        return mu;
    }

    real_t Gaussian::minValue() const 
    {
        return std::numeric_limits<real_t>().min();
    }

    real_t Gaussian::maxValue() const 
    {
        return std::numeric_limits<real_t>().max();
    }

    real_t Gaussian::pdf(real_t x) const 
    {
       return exp(-0.5 * pow((x - mu) / sigma, 2) )/ (sqrt(2.0 * M_PI) * sigma);
    }

    real_t Gaussian::cdf(real_t x) const 
    {   
        real_t erf = myerf((x - mu) / (sigma * sqrt(2)));
        return 0.5 * (1 + erf );
    }

    real_t Gaussian::myerf(real_t x) const
    {
        real_t erf; 
        erf = tanh((2/sqrt(M_PI)) *(x + (11 / 123) * pow(x, 3)));
        return erf;
    }

    real_t Gaussian::get_mu() const
    {
        return mu;
    }

    real_t Gaussian::get_sigma() const
    {
        return sigma;
    }
} 
