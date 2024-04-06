#ifndef DF_2DRV_H
#define DF_2DRV_H

#if (__cplusplus >= 202002L)

#include <iostream>
#include <vector>
#include <cmath>
#include <type_traits>
#include <concepts>
#include "basicfxn.h"

namespace DiceForge
{
    /* Helper functions for integration */

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