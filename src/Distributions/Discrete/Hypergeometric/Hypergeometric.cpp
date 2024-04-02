#include "Hypergeometric.h"
#include "basicfxn.h"
#include <algorithm>
#include <vector>
namespace DiceForge
{
    Hypergeometric::Hypergeometric(int32_t N, int32_t K, int32_t n) : N(N), K(K), n(n)
    {
        // constraints handling
        if (n > N || K > N || n < 0 || K < 0)
        {
           throw std::invalid_argument("invalid parameters (N, K, n)!"\
           "n and K must be positive, and n and K must not be larger than N");
        }

        pmfs.resize((std::min(n, K) + 1));       // pmf vector stores the probabilities
        cumulative.resize((std::min(n, K) + 1)); // cumulative sum vector
        if (n + K > N)
        {

            for (int i = 0; i < std::max(n + K - N, (int32_t)0); i++)
            {
                pmfs[i] = 0;
            }
        }
        int start = std::max(n + K - N, (int32_t)0);

        real_t ta = (real_t)nCr(K, start);
        real_t tb = (real_t)nCr(N - K, n - start);
        real_t tc = (real_t)nCr(N, n);

        pmfs[start] = (tb / tc) * ta;

        // using recurrence to calculate the probabilities instead of calling pmf function everytime
        for (int i = start + 1; i < std::min(n, K) + 1; i++)
        {
            pmfs[i] = pmfs[i - 1] * ((real_t)((K - i + 1) * (n - i + 1))) / (i * (N - K - n + i));
        }

        cumulative[0] = pmfs[0];
        for (int i = 1; i < std::min(n, K) + 1; i++)
        {
            cumulative[i] = cumulative[i - 1] + pmfs[i];
        }
    }
    // next function returns the index where cumulative[index] is just greater than r
    int_t Hypergeometric::next(real_t r)
    {
        for (int i = 0; i < std::min(n, K); i++)
        {
            /* code */
            if (cumulative[i] >= r)
            {
                return i;
            }
        }
        return (std::min(n, K));
    }

    // theoritical expectation
    real_t Hypergeometric::expectation() const
    {
        return (real_t)(n * K) / N;
    }

    // theoritical variance
    real_t Hypergeometric::variance() const
    {
        real_t num = n * K * (N - K) * (N - n);
        real_t den = N * N * (N - 1);
        return num / den;
    }

    // theoritical minimum
    int_t Hypergeometric::minValue() const
    {
        return std::max(n + K - N, (int32_t)0);
    }

    // theoritical maximum
    int_t Hypergeometric::maxValue() const
    {
        return (std::min(n, K));
    }

    // returns pmf of any value x
    real_t Hypergeometric::pmf(int_t x) const
    {
        if (x <= std::min(n, K) && x >= std::max(n + K - N, (int32_t)0))
            return (pmfs[x]);
        else
            return 0;
    }

    // returns cdf of any value x
    real_t
    Hypergeometric::cdf(int_t x) const
    {
        if (x < std::max(n + K - N, (int32_t)0))
            return 0;
        else if (x <= std::min(n, K))
            return cumulative[x];
        else
            return 1;
    }

}