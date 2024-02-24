#ifndef DICEFORGE_GIBBS_H
#define DICEFORGE_GIBBS_H

#include "distribution.h"

namespace DiceForge {
    class Gibbs : public DiceForge::Discrete {
        private:
            real_t *cumulative = nullptr;
            real_t *prob = nullptr;
            real_t *x_array = nullptr;
            int_t n = 0;
        public:
            void specify(real_t *x_arr, real_t *func_arr, int len, real_t beta);
            real_t next(real_t r) override;
            real_t variance() override;
            real_t expectation() override;
            real_t minValue() override;
            real_t maxValue() override;
            real_t pmf(real_t x) override;
            real_t cdf(real_t x) override;
    };
}


#endif
