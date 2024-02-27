#include "NegHypergeometric.h"
#include "../../basicfxn.h"

namespace DiceForge {
    
    NegHypergeometric::NegHypergeometric(uint_t N, uint_t K, uint_t r)
        : N(N), K(K), r(r)
    {
        if (K > N || r > N - K)
        {
            std::cerr << "Error :"
                        "\n\tDiceForge::NegHypergeometric::NegHypergeometric(uint_t N, uint_t K, uint_t r) : "
                        "\n\t\tReceived invalid parameters (N, K, r)\n" << std::endl;
            exit(EXIT_FAILURE);
        }

        // precalculate pmfs for faster random number generation
        pmfs = new real_t[K+1];
        for (int k = 0; k <= K; k++)
        {
            pmfs[k] = nCr(k + r - 1, k) * nCr(N - r - k, K - k) / real_t(nCr(N, K));    
        }
    }

    NegHypergeometric::~NegHypergeometric()
    {
        delete[] pmfs;
    }

    int_t NegHypergeometric::next(real_t r) 
    {
        real_t s = 0;
        for (int i = 0; i <= K; i++)
        {
            if (s < r <= s + pmfs[i])
            {
                return i;
            }
            s += pmfs[i];
        }

        return K;
    }

    real_t NegHypergeometric::variance() const
    {
        real_t a = r / real_t(N - K + 1);
        return a * (1 - a) * K * (N + 1) / real_t(N - K + 2);
    }

    real_t NegHypergeometric::expectation() const 
    {
        return real_t(r * K) / real_t(N - K + 1);
    }

    int_t NegHypergeometric::minValue() const
    {
        return 0;
    }

    int_t NegHypergeometric::maxValue() const
    {
        return K;
    }

    real_t NegHypergeometric::pmf(int_t k) const 
    {
        if (k > K || k < 0)
        {
            return 0;
        }
        return pmfs[k];
    }

    real_t NegHypergeometric::cdf(int_t k) const 
    {
        real_t cdf = 0;
        for (uint_t i = 0; i <= k; i++)
        {
            cdf += pmf(i);
        }
        
        return cdf;
    }
}