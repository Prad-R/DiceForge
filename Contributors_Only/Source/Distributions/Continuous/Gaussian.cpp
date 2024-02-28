#include "Gaussian.h"
#include <math.h>
#include <cmath>

namespace DiceForge
{            
    Gaussian::Gausssian(real_t mu, real_t sigma)
    : mu(mu), sigma(sigma)
    {
        if (sigma < std::numeric_limits<real_t>().epsilon())
        {
            std::cerr << "Error :"
                        "\n\tDiceForge::Gaussian::Gaussian(real_t mu, real_t sigma) : "
                        "\n\t\tValue of sigma must be positive\n" << std::endl;
            exit(EXIT_FAILURE);
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
       return exp(-0.5 * x * x) / sqrt(2.0 * M_PI);
    }

    real_t Gaussian::cdf(real_t x) const 
    {        
        return M_1_PI * atan((x - x0) * inv_gamma) + 0.5;
    }
} 
