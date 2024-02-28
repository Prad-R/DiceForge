#ifndef DF_BERNOULLI_H
#define DF_BERNOULLI_H

#include "../distribution.h"


namespace DiceForge {
    /// @brief DiceForge::Bernoulli - A Discrete Probability Distribution (Bernoulli) 
    class Bernoulli : public Discrete {
        private:
            float p;
        public:
            
          
            Bernoulli(real_t p);

            int_t next(real_t r) override final;
            real_t variance() const override final;
            real_t expectation() const override final;
            int_t minValue() const override final;
            int_t maxValue() const override final;
            real_t pmf(int_t k) const override final;
            real_t cdf(int_t k) const override final;
    };
}


#endif


