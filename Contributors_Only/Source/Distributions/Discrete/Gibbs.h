#ifndef DICEFORGE_GIBBS_H
#define DICEFORGE_GIBBS_H

#include "../distribution.h"

namespace DiceForge {
    class Gibbs : public DiceForge::Discrete {
        private:
            real_t *cumulative = nullptr;
            real_t *prob = nullptr;
            int_t *x_array = nullptr;
            int_t n = 0;
        public:
            void specify(int_t *x_arr, real_t *func_arr, int len, real_t beta);
            int_t next(real_t r) override;
            real_t variance() const override;
            real_t expectation() const override;
            int_t minValue() const override;
            int_t maxValue() const override;
            real_t pmf(int_t x) const override;
            real_t cdf(int_t x) const override;
    };
}


#endif
