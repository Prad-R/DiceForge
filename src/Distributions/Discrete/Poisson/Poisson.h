#ifndef DF_POISSON_H
#define DF_POISSON_H

#include "distribution.h"
#include "generator.h"

namespace DiceForge {
    
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
}

#endif
