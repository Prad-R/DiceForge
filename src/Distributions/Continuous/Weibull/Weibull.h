#ifndef DF_WEIBULL_H
#define DF_WEIBULL_H

#include "distribution.h"

namespace DiceForge {

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
}


#endif
