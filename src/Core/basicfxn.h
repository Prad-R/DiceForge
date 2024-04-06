#ifndef DF_BASICFXN_H
#define DF_BASICFXN_H

#include <iostream>
#include <functional>
#include <vector>
#include <limits>

#define _USE_MATH_DEFINES
#include <cmath>

#include "types.h"

namespace DiceForge
{
    /* Helper strucure for matrix operations */

    /* It is assumed that you are aware of contraints on the number of rows 
    * and columns while performing binary operations on two matrices and 
    * you will not abuse this poor struct */

    struct matrix_t
    {
        matrix_t(int r, int c);
        matrix_t(matrix_t& other);
        matrix_t(const matrix_t& other);
        ~matrix_t();

        const real_t* operator[](int i) const;
        real_t* operator[](int i);

        matrix_t operator*(const matrix_t& other) const;
        matrix_t operator+(const matrix_t& other) const;
        matrix_t operator-(const matrix_t& other) const;
        matrix_t operator-() const;        
        matrix_t transpose() const;

        real_t** m;

        const int r; // rows
        const int c; // cols
    };

    /* k-permutations of n */
    static inline uint_t nPr(uint_t n, uint_t r)
    {
        uint_t p = 1;
        for (uint_t i = n; i > n - r; i--)
            p *= i;

        return p;
    }

    /* uint128_t returns a 128-bit value
    * Moreover, this reduces the chance of overflow by applying division at each step
    * instead of performing it once at the last. */

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

    /* inverse of a 2x2 matrix */
    static matrix_t inverse2x2(const matrix_t& M)
    {
        real_t inv_det = 1 / (M[0][0] * M[1][1] - M[1][0] * M[0][1]);
        matrix_t inv = matrix_t(2, 2);
        inv.m[0][0] = M.m[1][1] * inv_det;
        inv.m[0][1] = -M.m[0][1] * inv_det;
        inv.m[1][0] = -M.m[1][0] * inv_det;
        inv.m[1][1] = M.m[0][0] * inv_det;
        
        return inv;
    }
    
    static real_t simpson(std::function<real_t(real_t)> f, real_t a, real_t b, size_t partitions = 1000000)
    {
        /*
        f = function we want to integrate
        a = start point on x axis
        b = end point on x axis
        h = step size, taken as a millionth of the diff btw a and b
        n = number of partitions, taken as a million here by default
        area = numerical area approximation using simpson's 1/3rd rule
        */
        real_t h, area, sum1, sum2, sum3, n;
        n = partitions;
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