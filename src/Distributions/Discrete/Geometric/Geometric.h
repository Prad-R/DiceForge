#ifndef DF_GEOMETRIC_H
#define DF_GEOMETRIC_H

#include "distribution.h"

namespace DiceForge {
    /// @brief DiceForge::Geometric - A Discrete Probability Distribution (Geometric) 
    class Geometric : public Discrete {
        private:
            float p;
        public:
            Geometric(real_t p);
            int_t next(real_t r);
            real_t variance() const override final;
            real_t expectation() const override final;
            int_t minValue() const override final;
            int_t maxValue() const override final;
            real_t pmf(int_t k) const override final;
            real_t cdf(int_t k) const override final;
    };
}


#endif