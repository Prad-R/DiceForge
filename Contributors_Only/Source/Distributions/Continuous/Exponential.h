#ifndef DF_EXPONENTIAL_H
#define DF_EXPONENTIAL_H

#include "../distribution.h"

namespace DiceForge
{
    class Exponential : public Continuous
    {
    private:
        real_t k;

    public:
        Exponential(real_t k);

        real_t next(real_t r) override final;
        real_t variance() const override final;
        real_t expectation() const override final;
        real_t minValue() const override final;
        real_t maxValue() const override final;
        real_t pdf(real_t x) const override final;
        real_t cdf(real_t x) const override final;
    };
}

#endif
