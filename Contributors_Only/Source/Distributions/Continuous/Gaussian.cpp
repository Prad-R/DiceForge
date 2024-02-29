#include "Gaussian.h"

namespace DiceForge
{            
    Gaussian::Gaussian(real_t mu, real_t sigma)
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
        std::vector<int> factorial = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
        real_t sum = 0; 
        for(int i = 0; i <= 10; i++)
        {
            sum += (pow(-1, i) * pow(x, 2 * i + 1))/((2 * i + 1) * pow(2, i) * factorial[i] );
        }
        return 0.5 + ( sum )/ sqrt(2.0 * M_PI);
    }
} 
