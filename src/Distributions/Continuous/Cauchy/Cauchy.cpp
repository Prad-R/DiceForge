#include "Cauchy.h"

namespace DiceForge
{            
    Cauchy::Cauchy(real_t x0, real_t gamma)
    : x0(x0), gamma(gamma), inv_gamma(1 / gamma)
    {
        if (gamma < std::numeric_limits<real_t>().epsilon())
        {
            std::cerr << "Error :"
                        "\n\tDiceForge::Cauchy::Cauchy(real_t x0, real_t gamma) : "
                        "\n\t\tValue of gamma must be positive\n" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    real_t Cauchy::next(real_t r) 
    {
        return gamma * tan(M_PI * (r - 0.5)) + x0;
    }

    real_t Cauchy::variance() const 
    {
        return std::numeric_limits<real_t>().quiet_NaN();
    }

    real_t Cauchy::expectation() const 
    {
        return std::numeric_limits<real_t>().quiet_NaN();
    }

    real_t Cauchy::minValue() const 
    {
        return std::numeric_limits<real_t>().min();
    }

    real_t Cauchy::maxValue() const 
    {
        return std::numeric_limits<real_t>().max();
    }

    real_t Cauchy::pdf(real_t x) const 
    {
        return M_1_PI * inv_gamma / (1 + (x - x0) * (x - x0) * inv_gamma * inv_gamma);
    }

    real_t Cauchy::cdf(real_t x) const 
    {        
        return M_1_PI * atan((x - x0) * inv_gamma) + 0.5;
    }
} 