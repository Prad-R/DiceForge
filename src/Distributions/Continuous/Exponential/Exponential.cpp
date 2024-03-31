#include "Exponential.h"

namespace DiceForge {

Exponential::Exponential(real_t k, real_t x0) {
    this->k = k;
    this->x0 = x0;

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
    return 1 / k;
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
    if (x < 0) {
        return 0; // PDF is defined only for non-negative x
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
Exponential fitToExponential(const std::vector<real_t> &x, const std::vector<real_t> &y, int max_iter = 10000, real_t epsilon = 1e-6, real_t alpha = 0.1) {
    if (x.size() != y.size()) {
        throw "Number of x-coordinates and y-coordinates provided in the data do not match!";
    }

    const int N = x.size();
    std::vector<real_t> z;
    z.reserve(N);

    for (real_t yval : y) {
        z.push_back(std::log(yval));
    }

    // y = e^(-k*(x-x0))
    // ln(y) = -k*(x-x0)
    // ln(y) = -k*x + k*x0
    // ln(y) = -k*x + c
    // z = -k*x + c
    // Initial guess for k
    real_t k = 1;
    // Initial guess for c
    real_t c = 1;

    // Gradient Descent
    for (int i = 0; i < max_iter; i++) {
        real_t k_grad = 0;
        real_t c_grad = 0;

        // Calculate the total gradient with respect to k and c
        for (int j = 0; j < N; j++) {
            real_t z_est = -k * x[j] + c;
            k_grad += (z_est - z[j]) * z_est / k;
            c_grad += (z_est - z[j]);
        }

        k_grad /= N;
        c_grad /= N;
        k -= alpha * k_grad;
        c -= alpha * c_grad;

        if (std::abs(alpha * k_grad) < epsilon && abs(alpha * c_grad) < epsilon) {
            // std::cout << alpha * k_grad << " " << alpha * c_grad << std::endl;
            // std::cout << "Converged in " << i << " iterations" << std::endl;
            break;
        }
    }

    real_t x0 = c / k;
    return Exponential(k, x0);
}
}