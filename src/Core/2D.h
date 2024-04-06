#ifndef DF_2DRV_H
#define DF_2DRV_H

#if (__cplusplus >= 202002L)

#include <iostream>
#include <vector>
#include <type_traits>
#include <concepts>

#define _USE_MATH_DEFINES
#include <cmath>

#include "basicfxn.h"

namespace DiceForge
{
    /* Helper functions for integration */

    template <typename valuetype = long double>
    auto weights()
    {
        using pair_t = std::pair<valuetype, valuetype>;
        using wts = std::vector<pair_t>;

        return wts
        {
                std::make_pair(0.0486909570091397, -0.024350292663424),
                std::make_pair(0.0486909570091397, 0.0243502926634244),
                std::make_pair(0.0485754674415034, -0.072993121787799),
                std::make_pair(0.0485754674415034, 0.0729931217877990),
                std::make_pair(0.0483447622348030, -0.121462819296120),
                std::make_pair(0.0483447622348030, 0.1214628192961206),
                std::make_pair(0.0479993885964583, -0.169644420423992),
                std::make_pair(0.0479993885964583, 0.1696444204239928),
                std::make_pair(0.0475401657148303, -0.217423643740007),
                std::make_pair(0.0475401657148303, 0.2174236437400071),
                std::make_pair(0.0469681828162100, -0.264687162208767),
                std::make_pair(0.0469681828162100, 0.2646871622087674),
                std::make_pair(0.0462847965813144, -0.311322871990211),
                std::make_pair(0.0462847965813144, 0.3113228719902110),
                std::make_pair(0.0454916279274181, -0.357220158337668),
                std::make_pair(0.0454916279274181, 0.3572201583376681),
                std::make_pair(0.0445905581637566, -0.402270157963991),
                std::make_pair(0.0445905581637566, 0.4022701579639916),
                std::make_pair(0.0435837245293235, -0.446366017253464),
                std::make_pair(0.0435837245293235, 0.4463660172534641),
                std::make_pair(0.0424735151236536, -0.489403145707053),
                std::make_pair(0.0424735151236536, 0.4894031457070530),
                std::make_pair(0.0412625632426235, -0.531279464019894),
                std::make_pair(0.0412625632426235, 0.5312794640198946),
                std::make_pair(0.0399537411327203, -0.571895646202634),
                std::make_pair(0.0399537411327203, 0.5718956462026340),
                std::make_pair(0.0385501531786156, -0.611155355172393),
                std::make_pair(0.0385501531786156, 0.6111553551723933),
                std::make_pair(0.0370551285402400, -0.648965471254657),
                std::make_pair(0.0370551285402400, 0.6489654712546573),
                std::make_pair(0.0354722132568824, -0.685236313054233),
                std::make_pair(0.0354722132568824, 0.6852363130542333),
                std::make_pair(0.0338051618371416, -0.719881850171610),
                std::make_pair(0.0338051618371416, 0.7198818501716109),
                std::make_pair(0.0320579283548516, -0.752819907260531),
                std::make_pair(0.0320579283548516, 0.7528199072605319),
                std::make_pair(0.0302346570724025, -0.783972358943341),
                std::make_pair(0.0302346570724025, 0.7839723589433414),
                std::make_pair(0.0283396726142595, -0.813265315122797),
                std::make_pair(0.0283396726142595, 0.8132653151227975),
                std::make_pair(0.0263774697150547, -0.840629296252580),
                std::make_pair(0.0263774697150547, 0.8406292962525803),
                std::make_pair(0.0243527025687109, -0.865999398154092),
                std::make_pair(0.0243527025687109, 0.8659993981540928),
                std::make_pair(0.0222701738083833, -0.889315445995114),
                std::make_pair(0.0222701738083833, 0.8893154459951141),
                std::make_pair(0.0201348231535302, -0.910522137078502),
                std::make_pair(0.0201348231535302, 0.9105221370785028),
                std::make_pair(0.0179517157756973, -0.929569172131939),
                std::make_pair(0.0179517157756973, 0.9295691721319396),
                std::make_pair(0.0157260304760247, -0.946411374858402),
                std::make_pair(0.0157260304760247, 0.9464113748584028),
                std::make_pair(0.0134630478967186, -0.961008799652053),
                std::make_pair(0.0134630478967186, 0.9610087996520538),
                std::make_pair(0.0111681394601311, -0.973326827789911),
                std::make_pair(0.0111681394601311, 0.9733268277899110),
                std::make_pair(0.0088467598263639, -0.983336253884626),
                std::make_pair(0.0088467598263639, 0.9833362538846260),
                std::make_pair(0.0065044579689784, -0.991013371476744),
                std::make_pair(0.0065044579689784, 0.9910133714767443),
                std::make_pair(0.0041470332605625, -0.996340116771955),
                std::make_pair(0.0041470332605625, 0.9963401167719553),
                std::make_pair(0.0017832807216964, -0.999305041735772),
                std::make_pair(0.0017832807216964, 0.9993050417357722)
            
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
    
    // defining a concept which is a predicate to constrain template type T is of arithmetic type
    template <typename T>
    concept arithmetic_c = std::is_arithmetic_v<std::remove_cvref_t<T>>;
    template <typename FuncType, typename ValueType>
    auto evaluate(FuncType &&f, ValueType value)
    {
        if constexpr (DiceForge::arithmetic_c<FuncType>)
        {
            using common_t = std::common_type_t<FuncType, ValueType>;

            return (common_t)f;
        }
        else if constexpr (requires { f(value); })
            return f(value); // if f is function, then evaluate f(value);
        else
            static_assert(arithmetic_c<FuncType> || requires { f(value); });
    }
    // helper function for evaluating value
    template <typename FuncType1, typename FuncType2, arithmetic_c ValueType>
    auto evaluate(std::tuple<FuncType1, FuncType2> funcs, /* bound of integral */
                  ValueType value)
    {
        return std::tuple{evaluate(std::get<0>(funcs), value), /*lower bound*/
                          evaluate(std::get<1>(funcs), value) /*upper bound*/};
    }

    /// @brief An integrator for functions in one variable, to be used as integrate(f, bounds)
    /// @param f the function to be integrated f(x)
    /// @param bounds integration bounds as a tuple
    /// @return The evaluated value of the integral
    template <typename FuncType, typename BoundType>
    BoundType integrate(FuncType &&f, std::tuple<BoundType, BoundType> bounds)
    {
        return gaussian_quadrature(f, std::get<0>(bounds), std::get<1>(bounds));
    }

    // use DiceForge::dx_dy for integration of f(x,y)dxdy and  DiceForge::dy_dx for integration of f(x,y)dydx

    // Integrate wrt x first, then wrt y in f(x, y)
    auto dx_dy = std::integer_sequence<int, 1, 0>{};
    // Integrate wrt y first, then wrt x in f(x, y)
    auto dy_dx = std::integer_sequence<int, 0, 1>{};

    /// @brief An integrator for functions in two variables, to be used as integrate(f, bounds_0, bounds_1, integration sequence)
    /// @param f the function to be integrated f(x, y)
    /// @param bounds_0 integration bounds of the first variable (x or y depending on integration sequence) as a tuple
    /// @param bounds_1 integration bounds of the second variable (x or y depending on integration sequence) as a tuple
    /// @param integration_sequence dx_dy or dy_dx (using DiceForge::dx_dy, DiceForge::dy_dx)
    /// @return The evaluated value of the integral
    template <auto First, auto Second, typename FuncType,
              typename Lower_0, typename Upper_0,
              typename Lower_1, typename Upper_1>
    std::common_type_t<Lower_0, Upper_0>
    integrate(FuncType &&f,
             std::tuple<Lower_0, Upper_0> bounds_0,
             std::tuple<Lower_1, Upper_1> bounds_1, std::integer_sequence<int, First, Second> integration_sequence)
    {
        using bound_t = std::common_type_t<Lower_0, Upper_0>;

        auto F0 = [&](auto v0)
        {
            auto F1 = [&](auto v1)
            {
                std::tuple<bound_t, bound_t> args{};

                std::get<First>(args) = v0;
                std::get<Second>(args) = v1;

                return std::apply(f, args);
            };

            return DiceForge::integrate(F1, evaluate(bounds_1, v0));
        };

        return DiceForge::integrate(F0, bounds_0);
    }
}

#endif
#endif