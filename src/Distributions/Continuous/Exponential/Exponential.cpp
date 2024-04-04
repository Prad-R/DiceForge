#include "Exponential.h"

namespace DiceForge {

    Exponential::Exponential(real_t k, real_t x0) : k(k), x0(x0) {
        // Check if k is positive
        if (k <= 0) {
            throw std::invalid_argument("Rate parameter (k) must be positive");
        }
    }

    real_t Exponential::next(real_t r) {
        // Inverse transform sampling for exponential distribution
        return -(log(1 - r) / k);
    }

    real_t Exponential::variance() const {
        // Variance formula for exponential distribution
        return 1 / (k * k);
    }

    real_t Exponential::expectation() const {
        // Expectation formula for exponential distribution
        return x0 + 1 / k;
    }

    real_t Exponential::minValue() const {
        // Minimum value for exponential distribution
        return std::numeric_limits<real_t>().min();
    }

    real_t Exponential::maxValue() const {
        // Maximum value for exponential distribution
        return std::numeric_limits<real_t>().max();
    }

    real_t Exponential::pdf(real_t x) const {
        if (x < x0) {
            return 0; // PDF is defined only for x > x0
        } else {
            // PDF formula for exponential distribution
            // Normalized
            return (exp(-k * (x - x0)));
        }
    }

    real_t Exponential::cdf(real_t x) const {
        // CDF formula for exponential distribution
        return (1 - exp(-k * (x - x0)));
    }

    real_t Exponential::get_k() const {
        return k;
    }
    real_t Exponential::get_x0() const {
        return x0;
    }

    // fit to exponential distribution using linear regression after taking log
    Exponential fitToExponential(const std::vector<real_t>& x, const std::vector<real_t>& y, int max_iter = 10000, real_t epsilon = 1e-6) {
        if (x.size() != y.size()) {
            throw "Number of x-coordinates and y-coordinates provided in the data do not match!";
        }

        const int N = x.size();

        std::vector<real_t> z, xr;
        z.reserve(N);
        xr.reserve(N);

        int valid_N = 0;
        real_t zmean = 0, xrmean = 0, x0_est = 0, ymax = 0;
        for (size_t i = 0; i < N; i++)
        {
            // Pick out only non-zero pdf data for log regression
            if (y[i] > 1e-12)
            {
                real_t zval = log(y[i]);
                z.push_back(zval);
                xr.push_back(x[i]);
                zmean += zval;
                xrmean += x[i];
                valid_N++;
            }

            if (y[i] > ymax)
            {
                ymax = y[i];
                x0_est = x[i];
            }
        }
        zmean /= valid_N;
        xrmean /= valid_N;

        // y = e^(-k*(x-x0))
        // ln(y) = -k*(x-x0)
        // ln(y) = -k*x + k*x0
        // ln(y) = -k*x + c
        // z = -k*x + c
        // Perform linear regression to find initial guess

        real_t Sxz = 0, Sxx = 0;
        for (size_t i = 0; i < valid_N; i++)
        {
            Sxz += (xr[i] - xrmean)*(z[i] - zmean);
            Sxx += (xr[i] - xrmean)*(xr[i] - xrmean);
        }

        real_t slope = Sxz/Sxx;
        real_t intercept = zmean - xrmean * slope;

        // Initial guess for k
        real_t k = -slope;
        // Initial guess for c
        real_t c = intercept;
        
        // Gradient Descent for Noisy Data
        for (int i = 0; i < max_iter; i++) {
            real_t k_grad = 0;
            real_t c_grad = 0;

            real_t alpha = 1 / sqrt(i + 1);

            // Calculate the total gradient with respect to k and c
            for (int j = 0; j < valid_N; j++) {
                real_t z_est = -k * xr[j] + c;
                k_grad += (z_est - z[j]) * z_est / k;
                c_grad += (z_est - z[j]);
            }

            k_grad /= valid_N;
            c_grad /= valid_N;

            if (std::abs(alpha * k_grad) < epsilon && abs(alpha * c_grad) < epsilon) {
                // std::cout << alpha * k_grad << " " << alpha * c_grad << std::endl;
                // std::cout << "Converged in " << i << " iterations" << std::endl;
                break;
            }
          
            real_t pred_k = k - alpha * k_grad;
            real_t pred_c = c - alpha * c_grad;

            // prevent possible incorrect jumping
            if ((pred_c / pred_c > 10 || pred_k / k > 10 || pred_c / c < 0.1 || pred_k / k < 0.1)) {
                alpha = alpha * 0.01;
            }
            
            k -= alpha * k_grad;
            c -= alpha * c_grad;
        }

        real_t x0 = fmin(c / k, x0_est);

        if (k < 0 || isnanf(k) || isnanf(x0))
        {
            throw std::runtime_error("Could not fit data to Exponential! Data is probably too noisy or not Exponential!");
        }

        return Exponential(k, x0);
    }
}