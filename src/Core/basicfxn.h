#ifndef DF_BASICFXN_H
#define DF_BASICFXN_H

#include <iostream>
#include <functional>

#include "types.h"

namespace DiceForge
{
    /* k-permutations of n */
    static inline uint_t nPr(uint_t n, uint_t r)
    {
        uint_t p = 1;
        for (uint_t i = n; i > n - r; i--)
            p *= i;

        return p;
    }

    /* 
        uint_t returns a 'long' value which is around 32-bits...
        uint128_t returns a 128-bit value
    */
    /* 
        Moreover, this reduces the chance of overflow by applying division at each step
        instead of at the last.
    */

    /* k-combinations of n */
    static inline uint128_t nCr(uint128_t n, uint128_t r)
    {
        if (r > n - r)
            r = n - r; // because C(n, r) == C(n, n - r)

        uint128_t ans = 1;
        uint128_t i;

        for (i = 1; i <= r; i++)
        {
            ans *= (uint128_t)(n - r + i);
            ans /= i;
        }

        return ans;
    }

    static real_t simpson(std::function<real_t(real_t)> f, real_t a, real_t b)
    {
        /*
        f = function we want to integrate
        a = start point on x axis
        b = end point on x axis
        h = step size, taken as a millionth of the diff btw a and b
        n = number of partitions, taken as a million here
        area = numerical area approximation using simpson's 1/3rd rule
        */
        real_t h, area, sum1, sum2, sum3, n;
        n = 1000000;
        h = (b - a) / n;
        sum1 = f(a) + f(b);
        sum2 = sum3 = 0;
        for (int i = 1; i < n; i = i + 2)
        {
            sum2 += f(a + i * h);
        }
        for (int i = 2; i <= n; i = i + 2)
        {
            sum3 += f(a + i * h);
        }
        area = h * (sum1 + 4 * sum2 + 2 * sum3) / 3;
        return area;
    }
}

#endif