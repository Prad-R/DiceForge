#include "Gaussian.h"
#include "basicfxn.h"

namespace DiceForge
{
    Gaussian::Gaussian(real_t mu, real_t sigma)
        : mu(mu), sigma(sigma)
    {
        if (sigma < std::numeric_limits<real_t>().epsilon())
        {
            std::cerr << "Error :"
                         "\n\tDiceForge::Gaussian::Gaussian(real_t mu, real_t sigma) : "
                         "\n\t\tValue of sigma must be positive\n"
                      << std::endl;
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
        return exp(-0.5 * pow((x - mu) / sigma, 2)) / (sqrt(2.0 * M_PI) * sigma);
    }

    real_t Gaussian::cdf(real_t x) const
    {
        real_t erf = myerf((x - mu) / (sigma * sqrt(2)));
        return 0.5 * (1 + erf);
    }

    real_t Gaussian::myerf(real_t x) const
    {
        real_t erf;
        erf = tanh((2 / sqrt(M_PI)) * (x + (11 / 123) * pow(x, 3)));
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

    Gaussian fitToGaussian(const std::vector<real_t> &x, const std::vector<real_t> &y, int max_iter, real_t epsilon)
    {
        if (x.size() != y.size())
        {
            throw "Number of x-coordinates and y-coordinates provided in the data do not match!";
        }

        const int N = x.size();

        // Initial guessing of mu, sigma
        real_t mu = 1, sigma = 1;

        real_t ysum = 0;
        real_t y2sum = 0;
        for (size_t i = 0; i < N; i++)
        {
            ysum += y[i];
            y2sum += y[i] * y[i];
        }
        real_t mu_guess = ysum / N;
        real_t sigma_guess = sqrt((y2sum / N) - mu_guess * mu_guess);

        real_t ymax = -INFINITY;
        for (size_t i = 0; i < N; i++)
        {
            // Check for outliers
            if (y[i] > ymax && y[i] - mu_guess < 3 * sigma_guess)
            {
                ymax = y[i];

                // Guess mu as the x value corresponding to maximum y
                mu = x[i];
            }
        }
        //computing max and min x values from given data
        real_t xmax = x[0], xmin = x[0];
        for (size_t i = 0; i < N; i++)
        {
            if (x[i] > xmax)
                xmax = x[i];
            if (x[i] < xmin)
                xmin = x[i];
        }
        //setting initial guess of sigma
        sigma = (xmax - xmin) / 6;

        // Start iterative updation
        for (size_t iter = 0; iter < max_iter; iter++)
        {
            // Compute Jacobian matrix and error vector
            matrix_t J(N, 2); // Jacobian matrix
            matrix_t R(N, 1); // Error vector

            for (size_t i = 0; i < N; i++)
            {
                real_t pdf = exp(-(x[i] - mu) * (x[i] - mu) / (2 * sigma * sigma)) / (sqrt(2 * M_PI) * sigma);
                // std::cout << sigma << std::endl;
                //  Partial derivatives of the Gaussian function with respect to mu and sigma
                real_t dpdf_dmu = (x[i] - mu) / (sigma * sigma) * pdf;
                real_t dpdf_dsigma = ((x[i] - mu) * (x[i] - mu) / (sigma * sigma * sigma) - 1 / sigma) * pdf;

                J[i][0] = -dpdf_dmu;
                J[i][1] = -dpdf_dsigma;

                R[i][0] = y[i] - pdf;
            }

            // Compute the transpose of the Jacobian matrix
            matrix_t JT = J.transpose();

            // Compute the move direction using the Gauss-Newton method
            matrix_t d = inverse2x2(JT * J) * JT * R;

            // Stop when error minimization is too little
            if (fabs(d[0][0]) < epsilon && fabs(d[1][0]) < epsilon)
            {
                break;
            }

            real_t alpha = 0.001;

            real_t pred_mu, pred_sigma;
            pred_mu = mu - alpha * d[0][0];
            pred_sigma = sigma - alpha * d[1][0];

            // prevent possible incorrect jumping
            if ((pred_mu / mu > 10 || pred_sigma / sigma > 10 || pred_mu / mu < 0.1 || pred_sigma / sigma < 0.1))
            {
                alpha = alpha * 0.0001;
            }

            // Gauss-Newton method
            mu = mu - alpha * d[0][0];
            sigma = sigma - alpha * d[1][0];
        }

        if (sigma < 0)
        {
            throw "Could not fit data to Gaussian!";
        }

        return Gaussian(mu, sigma);
    }
}
