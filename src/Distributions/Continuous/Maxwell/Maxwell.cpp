#include "Maxwell.h"
#include <math.h>
#include "basicfxn.h"

namespace DiceForge
{            
    Maxwell::Maxwell(real_t a) : a(a)
    {
        if (a<=0)
        {
            throw std::invalid_argument("Scaling factor a must be positive!");
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
        return sqrt(2 / M_PI) * x * x * exp(-1 * x * x / (2 * a * a)) / (a * a * a);
    }

    real_t Maxwell::cdf(real_t x) const 
    {        
        real_t beta = 1/(2*a*a);
        return beta * sqrt(beta)*sqrt(x)*exp(-x*beta)/tgamma(1.5);
    } 

    real_t Maxwell::get_a() const
    {
        return a;
    }

    Maxwell fitToMaxwell(const std::vector<real_t>& x, const std::vector<real_t>& y, int max_iter, real_t epsilon)
    {
        if (x.size() != y.size())
        {
            throw std::invalid_argument("Number of x-coordinates and y-coordinates provided in the data do no match!");
        }

        const int N=x.size();

        //initial guess of a using the fact that mode of the distribution is sqrt2 * a;
        real_t a = 1;
        real_t ymax = -INFINITY;
        for (size_t i = 0; i < N; i++)
        {
            if (y[i] > ymax) 
            {
                ymax = y[i];
                a = x[i] * M_SQRT1_2;
            }
        }

        // starting iterative updation 
        for (size_t i=0; i < max_iter; i++)
        {
            real_t J[N];                    // Jacobian matrix 
            real_t R[N];                    // Error vector R = (r_0, r_1, ..., r_N)
            real_t JTJ = 0, JTR = 0;

            for (size_t j = 0; j < N; j++)
            {
                real_t f = sqrt(2 / M_PI) * x[j] * x[j] * exp(-1 * x[j] * x[j] / (2 * a * a)) / (a * a * a);
                real_t dpdf_da = f * ((-3 / a) + (x[j] * x[j]) / (a * a * a));

                J[j] = -dpdf_da;
                R[j] = y[j] - f;
                JTJ += J[j] * J[j];
                JTR += J[j] * R[j];
            }

            // move direction 
            real_t d = JTR / JTJ;

            // stop when error minimization is too little 
            if (fabs(d) < epsilon){
                break;
            }

            real_t alpha = 1; 
            
            real_t pred_a;
            pred_a = a - alpha * d;

            // prevent possible incorrect jumping
            if ((pred_a / a > 100 || pred_a / a < 0.01))
            {
                alpha = alpha * 0.01;
            }

            // Gauss-Newton method
            a = a - alpha * d;
        }

        if (a < 0 || std::isnan(a))
        {
            throw std::runtime_error("Could not fit data to Maxwell distribution! Data is probably too noisy or not Maxwell!");
        }

        return Maxwell(a);
    }
}
