#ifndef DF_HYPERGEOMETRIC_H
#define DF_HYPERGEOMETRIC_H
#include <vector>
#include "distribution.h"

namespace DiceForge
{
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
}

#endif