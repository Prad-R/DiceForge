#ifndef DF_DISTRIBUTIONS_H
#define DF_DISTRIBUTIONS_H

#include "diceforge_core.h"
#include <functional>

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

    /// @brief Fits the given sample points (x, y=pdf(x)) to a Cauchy distribution using interquartile estimations followed by
    /// non-linear least squares regression using modified Gauss-Newton
    /// @param x list of x coordinates
    /// @param y list of corresponding y coordinates where y = pdf(x)
    /// @param max_iter maximum iterations to attempt to fit the data (higher to try for better fits)
    /// @param epsilon minimum acceptable error tolerance while attempting to fit the data (smaller to try for better fits)
    /// @return A Cauchy distribution fit to the given sample points
    Cauchy fitToCauchy(std::vector<real_t> x, std::vector<real_t> y, int max_iter = 10000, real_t epsilon = 1e-6);

    using PDF_Function = std::function<real_t(real_t)>;

    /// @brief DiceForge::CustomDistribution - Samples a continuous pdf, cutomised by the user 
    /// @note The CustomDistribution class assumes that the inputted probability density function (PDF) is a valid PDF over the specified range.
    /// @note Users are responsible for ensuring that the provided PDF satisfies the necessary conditions, such as non-negativity and integrability over the defined domain 
    class CustomDistribution : public Continuous {
    private:
        real_t lower_limit;
        real_t upper_limit;
        real_t m_expectation, m_variance;
        std::vector<std::pair<real_t, real_t>> cdf_values; // (input, cdf)
        PDF_Function pdf_function; // Declare pdf_function as a member variable

    public:
        /// @brief Constructor for Custom Distribution
        /// @param lower lower bound for the random variable (finite)
        /// @param upper upper bound for the random variable (finite)
        /// @param pdf probability density function describing the distribution
        /// @param n number of points where the pdf should be sampled for expectation, variance and cdf calculations (higher n provides better accuracy) 
        CustomDistribution(real_t lower, real_t upper, PDF_Function pdf, int n);

        /// @brief Returns the next value of the random variable described by the distribution
        /// @param r A random real number uniformly distributed between 0 and 1
        real_t next(real_t r);
        
        /// @brief Returns the expected value of the distribution
        /// @note The expectation value is approximate
        real_t expectation() const override final;
        
        /// @brief Returns the variance of the distribution
        /// @note The variance is an approximatation 
        real_t variance() const override final;

        /// @brief Returns the minimum possible value of the random variable described by the distribution
        real_t minValue() const override final;

        /// @brief Returns the maximum possible value of the random variable described by the distribution
        real_t maxValue() const override final;

        /// @brief Probabiliity density function (pdf) of the distribution
        /// @param x location where the pdf is to be evaluated
        real_t pdf(real_t x) const override final;

        /// @brief Cummalative density function (cdf) of the distribution
        /// @param x location where the pdf is to be evaluated
        /// @note Numerical methods of inegration are emplyed to find the cdf value. This does not ensure that the function itself is integrable over the given range.
        real_t cdf(real_t x) const override final;
    };
    
    /// @brief DiceForge::Exponential - A continuous exponential probability distribution
    class Exponential : public Continuous {
    private:
        real_t k;  // Rate parameter
        real_t x0; // Origin of the distribution
    public:        
        /// @brief Constructor for Exponential distribution.
        /// @param k Rate parameter for the exponential distribution.
        /// @param x0 Origin of the distribution.
        /// @note k > 0
        Exponential(real_t k, real_t x0 = 0);

        /// @brief Generate a random number from the exponential distribution.
        /// @param r Uniformly distributed random number in the range [0,1).
        /// @returns Random number from the exponential distribution.
        real_t next(real_t r);

        ///@brief Calculate the variance of the distribution.
        /// @returns Variance of the exponential distribution.
        real_t variance() const override final;
        
        /// @brief Calculate the expectation of the distribution.
        /// @returns Expectation of the exponential distribution.
        real_t expectation() const override final;
        
        /// @brief Get the minimum possible value in the distribution.
        /// @returns Minimum value of the exponential distribution.
        real_t minValue() const override final;

        /// @brief Get the maximum possible value in the distribution.
        /// @returns Maximum value of the exponential distribution.
        real_t maxValue() const override final;
        
        /// @brief Calculate the probability density function (PDF) of the distribution at a given point x.
        /// @param x Point at which to calculate the PDF.
        /// @returns PDF value at point x.
        real_t pdf(real_t x) const override final;
        
        /// @brief Calculate the cumulative distribution function (CDF) of the distribution at a given point x.
        /// @param x Point at which to calculate the CDF.
        /// @returns CDF value at point x.
        real_t cdf(real_t x) const override final;

        /// @brief Returns the rate parameter of the distribution
        real_t get_k() const;

        /// @brief Returns the origin of the distribution
        real_t get_x0() const;
    };
    
    /// @brief Fits the given sample points (x, y=pdf(x)) to an Exponential distribution using linear regression.
    /// using Linear Regression after taking log, Gradient Descent as Optimizer, Mean Squared Error as Loss Function
    /// @param x list of x coordinates
    /// @param y list of corresponding y coordinates where y = pdf(x)
    /// @param max_iter maximum iterations to attempt to fit the data (higher to try for better fits)
    /// @param epsilon minimum acceptable error tolerance while attempting to fit the data (smaller to try for better fits)
    /// @returns An Exponential distribution fit to the given sample points
    Exponential fitToExponential(const std::vector<real_t>& x, const std::vector<real_t>& y, int max_iter, real_t epsilon);

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

    /// @brief Fits the given sample points (x, y=pdf(x)) to a Gaussian distribution using non-linear least squares regression
    /// following Gauss-Newton methods
    /// @param x list of x coordinates
    /// @param y list of corresponding y coordinates where y = pdf(x)
    /// @param max_iter maximum iterations to attempt to fit the data (higher to try for better fits)
    /// @param epsilon minimum acceptable error tolerance while attempting to fit the data (smaller to try for better fits)
    /// @return A Gaussian distribution fit to the given sample points
    Gaussian fitToGaussian(const std::vector<real_t>& x, const std::vector<real_t>& y, int max_iter = 10000, real_t epsilon = 1e-6);

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
    
    /// @brief Fits the given sample points (x, y=pdf(x)) to a Maxwell distribution by non-linear least squares regression 
    /// using modified Gauss-Newton
    /// @param x list of x coordinates
    /// @param y list of corresponding y coordinates where y = pdf(x)
    /// @param max_iter maximum iterations to attempt to fit the data (higher to try for better fits)
    /// @param epsilon minimum acceptable error tolerance while attempting to fit the data (smaller to try for better fits)
    /// @return A Maxwell distribution fit to the given sample points
    Maxwell fitToMaxwell(const std::vector<real_t>& x, const std::vector<real_t>& y, int max_iter, real_t epsilon);

    /// @brief DiceForge::Weibull - A Continuous Probability Distribution (Weibull) 
    class Weibull : public Continuous {
        private:
            real_t k, lambda;
        public:
            /// @brief Initializes the Weibull distribution with scale gamma
            /// @param lambda scale factor of the distribution
            /// @param k shape factor of the distribution
            /// @note k > 0, lambda > 0
            Weibull(real_t lambda = 1, real_t k = 1);
        
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

            /// @brief Returns scale factor of the distribution
            real_t get_lambda() const;

            /// @brief Returns shape factor of the distribution
            real_t get_k() const;
    };    
    
    /// @brief Fits the given sample points (x, y=pdf(x)) to a Cauchy distribution using a two phase process - firstly a robust
    /// cdf based linear regression to calculate an estimate within 10% of the parameters followed secondly by Gauss-Newton method
    /// @param x list of x coordinates
    /// @param y list of corresponding y coordinates where y = pdf(x)
    /// @param max_iter maximum iterations to attempt to fit the data (higher to try for better fits)
    /// @param epsilon minimum acceptable error tolerance while attempting to fit the data (smaller to try for better fits)
    /// @return A Weibull distribution fit to the given sample points
    Weibull fitToWeibull(std::vector<real_t> x, std::vector<real_t> y, int max_iter, real_t epsilon);

    /// @brief DiceForge::Bernoulli - A Discrete Probability Distribution (Bernoulli) 
    class Bernoulli : public Discrete {
        private:
            float p;
        public:
            /// @brief Constructor for the Bernoulli Distribution
            /// @param p 
            Bernoulli(real_t p);
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            int_t next(real_t r);
            /// @brief Returns the theoretical variance of the distribution
            /// @returns p(1-p)
            real_t variance() const override final;
            /// @brief Returns the theoretical expectation value of the distribution
            /// @returns p
            real_t expectation() const override final;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns 0
            int_t minValue() const override final;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns 1
            int_t maxValue() const override final;
            /// @brief Probability mass function of the Bernoulli distribution
            real_t pmf(int_t k) const override final;            
            /// @brief Cumulative distribution function of the Bernoulli distribution
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
    
    /// @brief DiceForge::Gibbs - Gibbs distribution class (derived from Discrete)
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
        /// @brief Constructor to initialise private attributes of the distribution
        template <typename RandomAccessIterator1, typename RandomAccessIterator2>
        Gibbs(RandomAccessIterator1 sequence_first, RandomAccessIterator1 sequence_last,
              RandomAccessIterator2 function_first, RandomAccessIterator2 function_last,
              real_t beta){
            // Display error if lengths don't match
            if (sequence_last - sequence_first != function_last - function_first){
                throw std::invalid_argument("Lengths of sequence and function sequence must match!");
            }
            n = sequence_last - sequence_first;
            // Display error if n is not at least 1
            if (n <= 0) {
                throw std::invalid_argument("len must be positive!");
            }

            // Sort the pmf in increasing order of x (required for constructing cdf)
            std::pair<int_t, real_t> xy_arr[n];
            for (int i = 0; i < n; i++){
                xy_arr[i].first = sequence_first[i];
                xy_arr[i].second = function_first[i];
            }
            std::sort(xy_arr, xy_arr + n);

            // Display error if x values are not unique
            for (int i = 1; i < n; i++) {
                if (xy_arr[i].first == xy_arr[i - 1].first) {
                    throw std::invalid_argument("All x values in x_arr must be unique!");
                }
            }

            // Store x_array
            x_array = (int_t*)malloc(n * sizeof(int_t));
            for (int i = 0; i < n; i++){
                x_array[i] = xy_arr[i].first;
            }

            // Store pmf_array and cdf_array (prefix sum array of pmf_array)
            pmf_array = (real_t *)malloc(n * sizeof(real_t));
            cdf_array = (real_t *)malloc(n * sizeof(real_t));
            real_t prev = 0;
            for (int i = 0; i < n; i++){
                pmf_array[i] = exp(- beta * xy_arr[i].second);
                cdf_array[i] = prev + pmf_array[i];
                prev = cdf_array[i];
            }

            // Divide by Z(beta) = cdf_array[n - 1] for normalisation
            for (int i = 0; i < n; i++){
                pmf_array[i] /= cdf_array[n - 1];
                cdf_array[i] /= cdf_array[n - 1];
            }
        }
        // Destructor to free memory used by the 3 array attributes
        ~Gibbs();
        
        /// @brief Returns a sample of the random variable following the distribution given a 'r'
        /// @param r a uniformly distributed unit random variable
        int_t next(real_t r);
        
        /// @brief Returns the theoretical variance of the distribution
        real_t variance() const override;
        
        /// @brief Returns the theoretical expectation value of the distribution
        real_t expectation() const override;
        
        /// @brief Smallest number that can be generated in the distribution
        int_t minValue() const override;
        
        /// @brief Largest number that can be generated in the distribution
        int_t maxValue() const override;
        
        /// @brief Probability mass function for the Gibbs distribution
        real_t pmf(int_t x) const override;
        
        /// @brief Cumulative distribution function for the Gibbs distribution
        real_t cdf(int_t x) const override;
    };
    
    /// @brief DiceForge::Discrete - A discrete probability distribution
    /// @details This is the distribution you get when drawing balls without
    /// replacement from an urn with two colors. n is the number of balls you take,
    /// K is the number of red balls in the urn, N is the total number of balls in
    /// the urn, and the return value is the number of red balls you get.
    /// To regenerate samples of the variation this class uses inversion by chop-down
    /// search from start when parameters are small
    class Hypergeometric : public Discrete
    {
    private:
        int32_t N, K, n;
        std::vector<real_t> pmfs;
        std::vector<real_t> cumulative;
        // N - total size of the population
        // K - occurence in the population (successes)
        // n - sample numbers
        // constraints-(n<=N and k<=N and n>=0 and k>=0)
    public:
        /// @brief Constructor for the Hypergeometric distribution
        /// @param N total size of the population
        /// @param K occurence in the population (successes)
        /// @param n sample numbers
        /// @note n<=N, k<=N, n>=0, k>=0
        Hypergeometric(int32_t N, int32_t K, int32_t n); 
        /// @brief Returns the next value of the random variable described by the distribution
        /// @param r A random real number uniformly distributed between 0 and 1
        int_t next(real_t r);        
        /// @brief Returns the theoretical variance of the distribution
        real_t variance() const override;
        /// @brief Returns the theoretical expectation value of the distribution
        real_t expectation() const override;
        /// @brief Returns the minimum possible value of the random variable described by the distribution
        int_t minValue() const override;
        /// @brief Returns the maximum possible value of the random variable described by the distribution
        int_t maxValue() const override;
        /// @brief Probability mass function of the Hypergeometric distribution
        real_t pmf(int_t k) const override;       
        /// @brief Cumulative distribution function of the Hypergeometric distribution 
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
            /// @brief Cumulative distribution function of the Negative hypergeometric distribution
            /// @note Here it is the probability of encountering at most k "success" elements when the experiment is stopped
            real_t cdf(int_t k) const override final;
    };
    
    /// @brief DiceForge::Poisson - A discrete probability distribution
    class Poisson : public Discrete {
        private:
            real_t l,sq,lnl,g;
        public:
            /// @brief Constructor for the Poisson Distribution
            /// @param lambda lambda (> 0)
            Poisson(real_t lambda);

            /// @brief Returns the next value of the random variable described by the distribution
            /// @param rng A random number generator (derived from DiceForge::Generator) 
            template <typename T>
            int_t next(DiceForge::Generator<T>& rng)
            {
                real_t t,x,c;
                do{
                    do{
                        t=tan(M_PI*rng.next_unit());
                        x=sq*t+l;
                    } while (x<0);
                    x=floor(x);
                    c=0.9*(1+t*t)*exp(x*lnl-lgamma(x+1)-g);
                } while(rng.next_unit()>c);

                return int_t(x);
            }

            /// @brief Returns the theoretical variance of the distribution
            real_t variance() const override;

            /// @brief Returns the theoretical expectation value of the distribution
            real_t expectation() const override;

            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @returns 0
            int_t minValue() const override;

            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @returns positive infinity
            int_t maxValue() const override;
            
            /// @brief Probability mass function of the Poisson distribution
            real_t pmf(int_t x) const override;

            /// @brief Cumulative distribution function of the Poisson distribution
            real_t cdf(int_t x) const override;
    };
    
    /// @brief DiceForge::Geometric - A Discrete Probability Distribution (Geometric) 
    class Geometric : public Discrete {
        private:
            float p;
        public:
            /// @brief Constructor for the Geometric distribution
            /// @param p probability of "success"
            Geometric(real_t p);
            /// @brief Returns the next value of the random variable described by the distribution
            /// @param r A random real number uniformly distributed between 0 and 1
            int_t next(real_t r);            
            /// @brief Returns the theoretical variance of the distribution
            /// @returns (1-p)/(p^2)
            real_t variance() const override;
            /// @brief Returns the theoretical expectation value of the distribution
            /// @return 1/p
            real_t expectation() const override;
            /// @brief Returns the minimum possible value of the random variable described by the distribution
            /// @return 0
            int_t minValue() const override;
            /// @brief Returns the maximum possible value of the random variable described by the distribution
            /// @return positive infinity
            int_t maxValue() const override;
            /// @brief Probability mass function of the Geometric distribution
            real_t pmf(int_t k) const override;        
            /// @brief Cumulative distribution function of the Geometric distribution 
            real_t cdf(int_t k) const override;
    };
}



#endif