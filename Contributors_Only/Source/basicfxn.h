#ifndef DF_BASICFXN_H
#define DF_BASICFXN_H

#include "types.h"

#include <iostream>
#include <functional>

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

    /* k-combinations of n */
    static inline uint_t nCr(uint_t n, uint_t r)
    {
        uint_t nr = 1;
        for (uint_t i = n; i > n - r; i--)
            nr *= i;
        
        uint dr = 1;    
        for (uint i = 2; i <= r; i++)
            dr *= i;
        
        return nr / dr;
    }

    real_t simpson(std::function<real_t(real_t)> f, real_t a, real_t b)
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