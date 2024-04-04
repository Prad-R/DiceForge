#include "Maxwell.h"
#include <math.h>
#include "basicfxn.h"

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

    real_t fitToMaxwell(std::vector<real_t> x, std::vector<real_t> y, int max_iter, real_t epsilon)
    {
        if (x.size() != y.size())
        {
            throw std::runtime_error("Number of x-coordinates and y-coordinates provided in the data do no match!");
        }

        const int N=x.size();

        // sort the arrays in increasing x
        for (size_t i = 0; i < N-1; i++)
        {
            for (size_t j = 0; j < N-1-i; j++)
            {
                if (x[j] > x[j+1])
                {
                    real_t tx = x[j];
                    x[j] = x[j+1];
                    x[j+1] = tx;

                    real_t ty = y[j];
                    y[j] = y[j+1];
                    y[j+1] = ty;
                }
            }
        }     

        //initial guess of a;
        real_t a=1, mean=2*sqrt(2/M_PI);

        real_t ysum = 0;
        real_t y2sum = 0;
        for (size_t i = 0; i < N; i++)
        {
            ysum += y[i];
            y2sum += y[i] * y[i];
        }
        real_t mu = ysum / N;
        real_t stdev = sqrt((y2sum / N) - mu*mu);

        real_t ymax = -INFINITY;
        for (size_t i = 0; i < N; i++)
        {
            // check for outliers
            if (y[i] > ymax && y[i] - mu < 3 * stdev) 
            {
                ymax = y[i];

                // guessing the mean of the maxwell distribution
                mean = M_2_SQRTPI * x[i];
            }
        }

        // an approximation of a
        a = sqrt(M_PI/2) * (mean / 2);

        // starting iterative updation 
        for (size_t i=0; i < max_iter; i++)
        {
            matrix_t J = matrix_t(N, 1);    // Jacobian matrix 
            matrix_t R = matrix_t(N, 1);    // Error vector R = (r_0, r_1, ..., r_N)

            for (size_t j = 0; j < N; j++)
            {
                real_t f = sqrt(2 / M_PI) * x[j] * x[j] * exp(-1 * x[j] * x[j] / (2 * a * a)) / (a * a * a);
                real_t dpdf_da = f * ((-3 / a) + (x[j] * x[j]) / (a * a * a));

                J[j][0] = -dpdf_da;

                R[j][0] = y[j] - f;
            }

            matrix_t JT = J.transpose();

            // move direction 
            matrix_t d = (JT * J) * (JT * R);

            // stop when error minimization is too little 
            if (fabs(d[0][0]) < epsilon){
                break;
            }

            real_t alpha = 0.001; 
            
            real_t pred_a;
            pred_a = a - alpha * d[0][0];

            // prevent possible incorrect jumping
            if ((pred_a / a > 10 || pred_a / a < 0.1 ))
            {
                alpha = alpha * 0.0001;
            }

            // Gauss-Newton method
            a = a - alpha * d[0][0];
        }

        if (a < 0)
        {
            throw std::runtime_error("Could not fit data to Maxwell distribution!");
        }

        return Maxwell(a);
    }
}
