#ifndef DF_CAUCHY_H
#define DF_CAUCHY_H

#include "../distribution.h"

namespace DiceForge {
    class Cauchy : public Continuous {
        private:
            real_t x0, gamma, inv_gamma;
        public:

            /// @brief Initializes the Cauchy distribution about location x = x0 with scale gamma
            /// @param x0 centre of the distribution
            /// @param gamma scale factor of the distribution
            /// @note gamma > 0
            Cauchy(real_t x0 = 0, real_t gamma = 1);
            real_t next(real_t r) override;
            real_t variance() const override;
            real_t expectation() const override;
            real_t minValue() const override;
            real_t maxValue() const override;
            real_t pdf(real_t x) const override;
            real_t cdf(real_t x) const override;
    };
}


#endif
