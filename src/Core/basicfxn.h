#ifndef DF_BASICFXN_H
#define DF_BASICFXN_H

#include <iostream>
#include <functional>

#include "types.h"

namespace DiceForge
{
    /* Helper strucure for matrix operations */

    /* It is assumed that you are aware of contraints on the number of rows 
    * and columns while performing binary operations on two matrices and 
    * you will not abuse this poor struct*/

    struct matrix_t
    {
        matrix_t(int r, int c);
        matrix_t(matrix_t& other);
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

    /*
        uint_t returns a 'long' value which is around 32-bits...
        uint128_t returns a 128-bit value
    */
    /*
    /* 
        uint128_t returns a 128-bit value
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

    template <typename valuetype = long double>
    auto weights()
    {
        using pair_t = std::pair<valuetype, valuetype>;
        using wts = std::vector<pair_t>;

        return wts
        {
            {0.0486909570091397, -0.0243502926634244},
                {0.0486909570091397, 0.0243502926634244},
                {0.0485754674415034, -0.072993121787799},
                {0.0485754674415034, 0.0729931217877990},
                {0.0483447622348030, -0.121462819296120},
                {0.0483447622348030, 0.1214628192961206},
                {0.0479993885964583, -0.169644420423992},
                {0.0479993885964583, 0.1696444204239928},
                {0.0475401657148303, -0.217423643740007},
                {0.0475401657148303, 0.2174236437400071},
                {0.0469681828162100, -0.264687162208767},
                {0.0469681828162100, 0.2646871622087674},
                {0.0462847965813144, -0.311322871990211},
                {0.0462847965813144, 0.3113228719902110},
                {0.0454916279274181, -0.357220158337668},
                {0.0454916279274181, 0.3572201583376681},
                {0.0445905581637566, -0.402270157963991},
                {0.0445905581637566, 0.4022701579639916},
                {0.0435837245293235, -0.446366017253464},
                {0.0435837245293235, 0.4463660172534641},
                {0.0424735151236536, -0.489403145707053},
                {0.0424735151236536, 0.4894031457070530},
                {0.0412625632426235, -0.531279464019894},
                {0.0412625632426235, 0.5312794640198946},
                {0.0399537411327203, -0.571895646202634},
                {0.0399537411327203, 0.5718956462026340},
                {0.0385501531786156, -0.611155355172393},
                {0.0385501531786156, 0.6111553551723933},
                {0.0370551285402400, -0.648965471254657},
                {0.0370551285402400, 0.6489654712546573},
                {0.0354722132568824, -0.685236313054233},
                {0.0354722132568824, 0.6852363130542333},
                {0.0338051618371416, -0.719881850171610},
                {0.0338051618371416, 0.7198818501716109},
                {0.0320579283548516, -0.752819907260531},
                {0.0320579283548516, 0.7528199072605319},
                {0.0302346570724025, -0.783972358943341},
                {0.0302346570724025, 0.7839723589433414},
                {0.0283396726142595, -0.813265315122797},
                {0.0283396726142595, 0.8132653151227975},
                {0.0263774697150547, -0.840629296252580},
                {0.0263774697150547, 0.8406292962525803},
                {0.0243527025687109, -0.865999398154092},
                {0.0243527025687109, 0.8659993981540928},
                {0.0222701738083833, -0.889315445995114},
                {0.0222701738083833, 0.8893154459951141},
                {0.0201348231535302, -0.910522137078502},
                {0.0201348231535302, 0.9105221370785028},
                {0.0179517157756973, -0.929569172131939},
                {0.0179517157756973, 0.9295691721319396},
                {0.0157260304760247, -0.946411374858402},
                {0.0157260304760247, 0.9464113748584028},
                {0.0134630478967186, -0.961008799652053},
                {0.0134630478967186, 0.9610087996520538},
                {0.0111681394601311, -0.973326827789911},
                {0.0111681394601311, 0.9733268277899110},
                {0.0088467598263639, -0.983336253884626},
                {0.0088467598263639, 0.9833362538846260},
                {0.0065044579689784, -0.991013371476744},
                {0.0065044579689784, 0.9910133714767443},
                {0.0041470332605625, -0.996340116771955},
                {0.0041470332605625, 0.9963401167719553},
                {0.0017832807216964, -0.999305041735772},
            {
                0.0017832807216964, 0.9993050417357722
            }
        };
    }

    template <typename T1 = double, typename T2 = double (&)(double)>
    T1 gaussian_quadrature(T2 &&f, T1 x1, T1 x2)
    {
        auto weight = weights();
        auto a = (x2 - x1) / 2.0;
        auto b = (x2 + x1) / 2.0;
        T1 I{};
        for (auto &&[w, t] : weight)
        {
            I += w * f(a * t + b);
        }
        I *= a;
        return I;
    }
    template <typename T1 = double, typename T2 = double (&)(double)>
    T1 adaptive_gaussian_quadrature(T2 &&f, T1 a, T1 b)
    {
        constexpr T1 tolerance = std::numeric_limits<T1>::epsilon();

        auto c = (a + b) / 2;

        auto s1 = gaussian_quadrature(f, a, b);

        auto s2 = gaussian_quadrature(f, a, c) + gaussian_quadrature(f, c, b);

        auto diff = std::abs(s1 - s2);

        if (diff <= tolerance)
        {
            return s2;
        }
        else
        {
            return adaptive_gaussian_quadrature(f, a, c) + adaptive_gaussian_quadrature(f, c, b);
        }
    }
    template <typename FuncType, typename BoundType>
    BoundType integrals(FuncType &&f, std::tuple<BoundType, BoundType> bound)
    {
        return gaussian_quadrature(f, std::get<0>(bound), std::get<1>(bound));
    }
}

#endif