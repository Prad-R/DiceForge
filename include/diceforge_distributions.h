#ifndef DF_DISTRIBUTIONS_H
#define DF_DISTRIBUTIONS_H

#include "diceforge_core.h"

namespace DiceForge {
    /// @brief DiceForge::Cauchy - A Continuous Probability Distribution (Cauchy) 
    class Cauchy : public Continuous {
        private:
            real_t x0, gamma, inv_gamma;
        public:
            /// @brief Initializes the Cauchy distribution about location x = x0 with scale gamma
            /// @param x0 centre of the distribution
            /// @param gamma scale factor of the distribution
            /// @note gamma > 0
            Cauchy(real_t x0 = 0, real_t gamma = 1);
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            real_t next(real_t r);
            /// @brief Returns the theoretical variance of the distribution
            /// @note The variation of a Cauchy distribution is undefined
            /// @returns NaN
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            /// @note The expectation value of a Cauchy distribution is undefined
            /// @returns NaN
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns negative infinity
            real_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns positive infinity
            real_t maxValue() const override final;
            /// @brief Probability density function of the Cauchy distribution
            real_t pdf(real_t x) const override final;
            /// @brief Cumulative distribution function of the Cauchy distribution
            real_t cdf(real_t x) const override final;
            /// @brief Returns x0 (centre of the distribution) 
            real_t get_x0() const;
            /// @brief Returns gamma (scale factor of the distribution) 
            real_t get_gamma() const;
    };
    
    /// @brief Fits the given sample points (x, y=pdf(x)) to a Cauchy distribution using non-linear least squares regression
    /// following Gauss-Newton methods
    /// @param x list of x coordinates
    /// @param y list of corresponding y coordinates where y = pdf(x)
    /// @param max_iter maximum iterations to attempt to fit the data (higher to try for better fits)
    /// @param epsilon minimum acceptable error tolerance while attempting to fit the data (smaller to try for better fits)
    /// @return A Cauchy distribution fit to the given sample points
    Cauchy fitToCauchy(const std::vector<real_t>& x, const std::vector<real_t>& y, int max_iter = 10000, real_t epsilon = 1e-6);

    /// @brief DiceForge::Exponential - A continuous exponential probability distribution
    class Exponential : public Continuous
    {
    private:
        real_t k; // Rate parameter
    public:
        /**
         * @brief Constructor for Exponential distribution.
         * @param k Rate parameter for the exponential distribution.
         */
        Exponential(real_t k);
        /**
         * @brief Generate a random number from the exponential distribution.
         * @param r Random number in the range [0,1).
         * @return Random number from the exponential distribution.
         */
        real_t next(real_t r);
        /**
         * @brief Calculate the variance of the distribution.
         * @return Variance of the exponential distribution.
         */
        real_t variance() const override final;
        /**
         * @brief Calculate the expectation of the distribution.
         * @return Expectation of the exponential distribution.
         */
        real_t expectation() const override final;
        /**
         * @brief Get the minimum possible value in the distribution.
         * @return Minimum value of the exponential distribution.
         */
        real_t minValue() const override final;
        /**
         * @brief Get the maximum possible value in the distribution.
         * @return Maximum value of the exponential distribution.
         */
        real_t maxValue() const override final;
        /**
         * @brief Calculate the probability density function (PDF) of the distribution at a given point x.
         * @param x Point at which to calculate the PDF.
         * @return PDF value at point x.
         */
        real_t pdf(real_t x) const override final;
        /**
         * @brief Calculate the cumulative distribution function (CDF) of the distribution at a given point x.
         * @param x Point at which to calculate the CDF.
         * @return CDF value at point x.
         */
        real_t cdf(real_t x) const override final;
        /// @brief Returns the rate parameter of the distribution 
        real_t get_k() const;
    };

    /// @brief DiceForge::Gaussian - A Continuous Probability Distribution (Gaussian) 
    class Gaussian : public Continuous {
        private:
            real_t mu, sigma;
            real_t myerf(real_t x) const;
        public:
            /// @brief Initializes the Gaussian distribution about location x = mu with standard deviation sigma
            /// @param mu mean of the distribution
            /// @param sigma standard deviation of the distribution
            Gaussian(real_t mu = 0, real_t sigma = 1);
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r1 A random real number uniformly distributed between 0 and 1
            /// @param r2 A random real number uniformly distributed between 0 and 1
            real_t next(real_t r1, real_t r2);
            /// @brief Returns the theoretical variance of the distribution
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            /// @returns mean of the distribution
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns negative infinity
            real_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns positive infinity
            real_t maxValue() const override final;
            /// @brief Probability density function of the Gaussian distribution
            real_t pdf(real_t x) const override final;
            /// @brief Cumulative distribution function of the Gaussian distribution
            real_t cdf(real_t x) const override final;
            /// @brief Returns mean of the distribution
            real_t get_mu() const;
            /// @brief Returns standard deviation of the distribution
            real_t get_sigma() const;
    };

    /// @brief DiceForge::Maxwell - A Continuous Probability Distribution (Maxwell) 
    class Maxwell : public Continuous
    {
        private:
            real_t a;
        public:
            /// @brief Initializes the Maxwell distribution with scale "a"
            /// @param a scale factor of the distribution
            /// @note a > 0
            Maxwell(real_t a = 1);
            /// @brief Generates a random number from the Maxwell Distribution
            /// @param r1 A random real number uniformly distributed between 0 and 1
            /// @param r2 A random real number uniformly distributed between 0 and 1
            /// @param r3 A random real number uniformly distributed between 0 and 1
            real_t next(real_t r1, real_t r2, real_t r3);
            /// @brief Returns the theoretical variance of the distribution
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns zero
            real_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns positive infinity
            real_t maxValue() const override final;
            /// @brief Probability density function of the Maxwell distribution
            real_t pdf(real_t x) const override final;
            /// @brief Cumulative distribution function of the Maxwell distribution
            real_t cdf(real_t x) const override final;
            /// @brief Returns the scale factor of the distribution 
            real_t get_a() const;
    };

    /// @brief DiceForge::Weibull - A Continuous Probability Distribution (Weibull) 
    class Weibull : public Continuous {
        private:
            real_t shift, k, lambda;
        public:
            /// @brief Initializes the Weibull distribution about location x = x0 with scale gamma
            /// @param shift shift parameter of distribution
            /// @param lambda scale factor of the distribution
            /// @param k shape factor of the distribution
            /// @note k > 0, lambda > 0
            Weibull(real_t lambda = 1, real_t k = 1, real_t shift = 0);
        
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            real_t next(real_t r);
        
            /// @brief Returns the theoretical variance of the distribution
            /// @note The variation of a Weibull distribution is undefined
            /// @returns NaN
            real_t variance() const override final;
        
            /// @brief Returns the theoretical expectation value of the distribution
            /// @note The expectation value of a Weibull distribution is undefined
            /// @returns NaN
            real_t expectation() const override final;
        
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns 0
            real_t minValue() const override final;
        
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns positive infinity
            real_t maxValue() const override final;
        
            /// @brief Probability density function of the Weibull distribution
            real_t pdf(real_t x) const override final;
        
            /// @brief Cumulative distribution function of the Weibull distribution
            real_t cdf(real_t x) const override final;

            /// @brief Returns shift parameter of distribution
            real_t get_shift() const;

            /// @brief Returns scale factor of the distribution
            real_t get_lambda() const;

            /// @brief Returns shape factor of the distribution
            real_t get_k() const;
    };

    /// @brief DiceForge::Bernoulli - A Discrete Probability Distribution (Bernoulli) 
    class Bernoulli : public Discrete {
        private:
            float p;
        public:
            Bernoulli(real_t p);
            int_t next(real_t r);
            real_t variance() const override final;
            real_t expectation() const override final;
            int_t minValue() const override final;
            int_t maxValue() const override final;
            real_t pmf(int_t k) const override final;
            real_t cdf(int_t k) const override final;
    };

    /// @brief DiceForge::Binomial - A Discrete Probability Distribution (Binomial Distribution) 
    class Binomial : public Discrete {
        private:
            uint_t n;
            real_t p;
            std::vector<real_t> pmfs;
        public:
            /// @brief Initializes the Binomial Distribution with (n, p)
            /// @param n number of trials 
            /// @param p probability of "success" in each trial
            /// @note 0 <= p <= 1
            Binomial(uint_t n, real_t p);
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            int_t next(real_t r);
            /// @brief Returns the theoretical variance of the distribution
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            int_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            int_t maxValue() const override final;
            /// @brief Probability mass function of the Binomial distribution
            /// @note Here it is the probability of encountering exactly k "success" trials
            real_t pmf(int_t k) const override final;
            /// @brief Cumulative distribution function of the Binomial distribution
            real_t cdf(int_t k) const override final;
    };

    // Gibbs distribution class (derived from Discrete)
    class Gibbs : public Discrete {
        private:
            // Array to store cdf
            real_t *cdf_array = nullptr;
            // Array to store pmf
            real_t *pmf_array = nullptr;
            // Array to store x values (output values)
            int_t *x_array = nullptr;
            // Length of all 3 arrays
            int_t n = 0;
        public:
            // Constructor to initialise the private attributes above
            Gibbs(int_t *x_arr, real_t *func_arr, int len, real_t beta);
            // Destructor to free memory used by the 3 array attributes
            ~Gibbs();
            /* next(r) [Integer] - Returns a random integer following the distribution given a 'r'
             * r is a uniformly distributed unit random variable */
            int_t next(real_t r);
            /* variance() [Real] - Returns the variance of the distribution */
            real_t variance() const override;
            /* expectation() [Real] - Returns the expectation value of the distribution */
            real_t expectation() const override;
            /* minValue() [Integer] - Smallest number that can be generated in the distribution */
            int_t minValue() const override;
            /* maxValue() [Integer] - Largest number that can be generated in the distribution */
            int_t maxValue() const override;
            /* pdf(x) [Real] - Probability mass function */
            real_t pmf(int_t x) const override;
            /* cdf(x) [Real] - Cumulative distribution function */
            real_t cdf(int_t x) const override;
    };

    // hypergeometric distribution class- a discrete random number generator
    /*
    This function generates a random variate with the hypergeometric
    distribution. This is the distribution you get when drawing balls without
    replacement from an urn with two colors. n is the number of balls you take,
    K is the number of red balls in the urn, N is the total number of balls in
    the urn, and the return value is the number of red balls you get.

    This function uses inversion by chop-down search from start when
    parameters are small
    */
    class Hypergeometric : public Discrete
    {
    private:
        int32_t N, K, n;
        std::vector<real_t> pmfs;
        std::vector<real_t> cumulative;
        // N - total size of the population
        // K- occurence in the population (successes)
        // n- sample numbers
        // constraints-(n<=N and k<=N and n>=0 and k>=0)
    public:
        Hypergeometric(int32_t N, int32_t K, int32_t n); // constructor for hypergeometric class
        int_t next(real_t r);
        real_t variance() const override;
        real_t expectation() const override;
        int_t minValue() const override;
        int_t maxValue() const override;
        real_t pmf(int_t k) const override;
        real_t cdf(int_t k) const override;
    };

    /// @brief DiceForge::NegHypergeometric - A Discrete Probability Distribution (Negative Hypergeometric) 
    class NegHypergeometric : public Discrete {
        private:
            uint_t N, K, r;
            real_t* pmfs;
        public:
            /// @brief Initializes the Negative Hypergeometric Distribution with (N, K, r)
            /// @param N size of the population 
            /// @param K number of "success" elements in the population
            /// @param r number of "failure" elements to be encountered before experiment is stopped
            /// @note 0 <= K <= N, 0 <= r <= N - K for a valid distribution
            NegHypergeometric(uint_t N, uint_t K, uint_t r);
            /// @brief Default destuctor
            ~NegHypergeometric();
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            int_t next(real_t r);
            /// @brief Returns the theoretical variance of the distribution
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            int_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            int_t maxValue() const override final;
            /// @brief Probabiliity mass function of the Negative hypergeometric distribution
            /// @note Here it is the probability of encountering exactly k "success" elements when the experiment is stopped
            real_t pmf(int_t k) const override final;
            /// @brief Probabiliity distribution function of the Negative hypergeometric distribution
            /// @note Here it is the probability of encountering at most k "success" elements when the experiment is stopped
            real_t cdf(int_t k) const override final;
    };

    template <typename T>
    class Poisson : public Discrete {
        private:
            int64_t seed;
            real_t l,sq,lnl,g;
            real_t getran();
            T generator;
        public:
            // Constructor to initialise the private attributes above
            Poisson(real_t, int32_t);

            /* Returns next number */
            int_t next();
            /* variance() [Real] - Returns the variance of the distribution */
            real_t variance() const override;
            /* expectation() [Real] - Returns the expectation value of the distribution */
            real_t expectation() const override;
            /* minValue() [Integer] - Smallest number that can be generated in the distribution  */
            int_t minValue() const override;
            /* maxValue() [Integer] - Largest number that can be generated in the distribution */
            int_t maxValue() const override;
            /* pdf(x) [Real] - Probability mass function */
            real_t pmf(int_t x) const override;
            /* cdf(x) [Real] - Cumulative distribution function */
            real_t cdf(int_t x) const override;
    };
}



#endif