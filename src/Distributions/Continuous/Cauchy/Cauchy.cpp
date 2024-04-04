#include "Cauchy.h"
#include "basicfxn.h"

namespace DiceForge
{            
    Cauchy::Cauchy(real_t x0, real_t gamma)
    : x0(x0), gamma(gamma), inv_gamma(1 / gamma)
    {
        if (gamma < std::numeric_limits<real_t>().epsilon())
        {
            throw std::invalid_argument("gamma must be positive!");
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

    real_t Cauchy::get_x0() const 
    {
        return x0;
    }

    real_t Cauchy::get_gamma() const 
    {        
        return gamma;
    }

    Cauchy fitToCauchy(std::vector<real_t> x, std::vector<real_t> y, int max_iter, real_t epsilon)
    {
        if (x.size() != y.size())
        {
            throw std::invalid_argument("Number of x-coordinates and y-coordinates provided in the data do not match!");
        }

        const int N = x.size();

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

        // initial guessing of x0, gamma
        real_t x0 = 0, gamma = 1;

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

                // guess x0 as the x value corresponding to maximum y
                x0 = x[i];
            }
        }

        // interquartile guess works reasonably well for gamma
        gamma = (x[(int)round(3 * N/4.0)] - x[(int)round(N/4.0)]) * 0.4;

        // start iterative updation
        for (size_t i = 0; i < max_iter; i++)
        {
            real_t inv_gamma = 1 / gamma;

            // r_i = y[i] - pdf(x0, gamma, x[i])
            // we try to minimize sum (r_i)^2 and iteratively update x0, inv_gamma

            matrix_t J = matrix_t(N, 2);    // Jacobian matrix
            matrix_t R = matrix_t(N, 1);    // Error vector R = (r_0, r_1, ..., r_N)

            for (size_t i = 0; i < N; i++)
            {
                real_t q1 = (x[i] - x0) * inv_gamma;
                real_t q2 = (1 + q1 * q1) * (1 + q1 * q1);      
                real_t dpdf_dx0 = 2 * M_1_PI * q1 * inv_gamma * inv_gamma / q2; 
                real_t dpdf_dgamma = - M_1_PI * (1 + 3 * q1 * q1) * inv_gamma * inv_gamma / q2;

                J[i][0] = -dpdf_dx0;
                J[i][1] = -dpdf_dgamma;

                R[i][0] = y[i] - M_1_PI * inv_gamma / (1 + (x[i] - x0) * (x[i] - x0) * inv_gamma * inv_gamma);
            }

            matrix_t JT = J.transpose();

            // move direction
            matrix_t d = inverse2x2(JT * J) * JT * R;

            // stop when error minimization is too little
            if (fabs(d[0][0]) < epsilon && fabs(d[1][0]) < epsilon)
                break;

            // make finer refinements later on
            // c/sqrt(i) works as a reasonable good learning rate for a cauchy fit
            real_t alpha = 1/sqrt(i+1); 
            
            real_t pred_x0, pred_gamma;
            pred_x0 = x0 - alpha * d[0][0];
            pred_gamma = gamma - alpha * d[1][0];

            // prevent possible incorrect jumping
            if ((pred_x0 / x0 > 10 || pred_gamma / gamma > 10 || pred_x0 / x0 < 0.1 || pred_gamma / gamma < 0.1))
            {
                alpha = alpha * 0.01;
            }

            // Gauss-Newton method
            x0 = x0 - alpha * d[0][0];
            gamma = gamma - alpha * d[1][0];
        }

        if (gamma < 0 || isnanf(x0) || isnanf(gamma))
        {
            throw std::runtime_error("Could not fit data to Cauchy! Data is probably too noisy or not Cauchy!");
        }

        return Cauchy(x0, gamma);
    }
} 