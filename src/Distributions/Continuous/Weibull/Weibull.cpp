#include "Weibull.h"
#include "basicfxn.h"

namespace DiceForge{            
    Weibull::Weibull(real_t lambda, real_t k)
            : lambda(lambda), k(k) {
        if (lambda < std::numeric_limits<real_t>().epsilon()){
            throw std::invalid_argument("Value of lambda(scale factor) must be positive!");
        }

        if (k < std::numeric_limits<real_t>().epsilon()){
            throw std::invalid_argument("Value of k(shape factor) must be positive!");
        }
    }

    real_t Weibull::next(real_t r) {
        return lambda * std::pow(-std::log(1 - r), 1/k);
    }

    real_t Weibull::variance() const{
        return pow(lambda, 2) * (std::tgamma(1 + 2/k) - pow(std::tgamma(1 + 1/k), 2));
    }

    real_t Weibull::expectation() const {
        return lambda * std::tgamma(1 + 1/k);
    }

    real_t Weibull::minValue() const{
        return 0;
    }

    real_t Weibull::maxValue() const{
        return std::numeric_limits<real_t>().max();
    }

    real_t Weibull::pdf(real_t x) const {
        if(x < 0)
            return 0;
        x = x / lambda;
        return (k/lambda) * std::pow(x, k-1) * exp(-std::pow(x, k));
    }

    real_t Weibull::cdf(real_t x) const{        
        if(x < 0)
            return 0;
        x = x / lambda;
        return 1 - exp(-std::pow(x, k));
    }

    real_t Weibull::get_lambda() const
    {
        return lambda;
    }

    real_t Weibull::get_k() const
    {
        return k;
    }

    Weibull fitToWeibull(std::vector<real_t> x, std::vector<real_t> y, int max_iter, real_t epsilon) 
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

        real_t yr_mean = 0, xr_mean = 0;

        std::vector<real_t> yreg, xreg;
        yreg.reserve(N); xreg.reserve(N);
        int valid_N = 0;

        for (size_t i = 1; i < N; i++)
        {
            real_t cdf = 0;
            for (size_t j = 1; j <= i; j++)
            {
                cdf += 0.5 * (y[j] + y[j-1]) * (x[j] - x[j-1]);   
            }

            if (cdf > 1e-12 && cdf < 1)
            {
                real_t yr = log(-log(1-cdf)), xr = log(x[i]);
                yreg.emplace_back(yr);
                xreg.emplace_back(xr);
                yr_mean += yr;
                xr_mean += xr;
                valid_N++;
            }
        }

        yr_mean /= valid_N;
        xr_mean /= valid_N;

        real_t Sxy = 0, Sxx = 0;
        for (size_t i = 0; i < valid_N; i++)
        {
            Sxy += (xreg[i] - xr_mean)*(yreg[i] - yr_mean);
            Sxx += (xreg[i] - xr_mean)*(xreg[i] - xr_mean);
        }

        real_t slope = Sxy/Sxx;
        real_t intercept = yr_mean - xr_mean * slope;

        real_t k = slope;
        real_t lambda = pow(exp(intercept / (-slope)), 0.7);
        real_t shift = 0;

        // start iterative updation
        for (size_t i = 0; i < max_iter; i++)
        {
            // r_i = y[i] - pdf(k, lambda)
            // we try to minimize sum (r_i)^2 and iteratively update k, lambda

            matrix_t J = matrix_t(N, 2);    // Jacobian matrix
            matrix_t R = matrix_t(N, 1);    // Error vector R = (r_0, r_1, ..., r_N)

            for (size_t i = 0; i < N; i++)
            {
                real_t z = (x[i] - shift) / lambda;
                real_t pdfexpr = (k/lambda) * pow(z, k-1) * exp( - pow(z, k));

                real_t dpdf_dlambda = pdfexpr * (pow(z, k) - 1) * (k/lambda); 
                real_t dpdf_dk = pdfexpr * (1/k + log(z) * (1 - pow(z, k)));

                J[i][0] = - dpdf_dlambda;
                J[i][1] = - dpdf_dk;

                R[i][0] = y[i] - pdfexpr;
            }

            matrix_t JT = J.transpose();

            // move direction
            matrix_t d = inverse2x2(JT * J) * JT * R;

            // stop when error minimization is too little
            if (fabs(d[0][0]) < epsilon && fabs(d[1][0]) < epsilon)
                break;

            // make finer refinements later on
            // c/i^0.1 works as a reasonable good learning rate for a weibull fit
            real_t alpha = 1/pow(i+1, 0.1); 
            
            real_t pred_lambda, pred_k;
            pred_lambda = lambda - alpha * d[0][0];
            pred_k = k - alpha * d[1][0];

            // prevent possible incorrect jumping
            if ((pred_lambda / lambda > 10 || pred_k / k > 10 || pred_lambda / lambda < 0.1 || pred_k / k < 0.1)) {
                alpha = alpha * 0.01;
            }

            // Gauss-Newton method
            lambda = lambda - alpha * d[0][0];
            k = k - alpha * d[1][0];
        }

        if (lambda <= 0 || k <= 0 || std::isnan(lambda) || std::isnan(k))
        {
            throw std::runtime_error("Could not fit data to Weibull! Data is probably too noisy or not Weibull!");
        }

        return Weibull(lambda, k);
    }
}