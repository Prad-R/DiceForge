#include <iostream>
#include <vector>
#include <cmath>
#include <type_traits>
#include <concepts>
#include "basicfxn.h"
namespace DiceForge
{
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
    template <typename FuncType1, typename FuncType2, arithmetic_c ValueType>
    auto evaluate(std::tuple<FuncType1, FuncType2> funcs, /* bound of integral */
                  ValueType value)
    {
        return std::tuple{evaluate(std::get<0>(funcs), value), /*lower bound*/
                          evaluate(std::get<1>(funcs), value) /*upper bound*/};
    }

    // use DiceForge::dx_dy for integration of f(x,y)dxdy and  DiceForge::dy_dx for integration of f(x,y)dydx
    auto dx_dy = std::integer_sequence<int, 1, 0>{};
    auto dy_dx = std::integer_sequence<int, 0, 1>{};

    template <auto First, auto Second, typename FuncType,
              typename Lower_0, typename Upper_0,
              typename Lower_1, typename Upper_1>
    std::common_type_t<Lower_0, Upper_0>
    integral(FuncType &&f,
             std::tuple<Lower_0, Upper_0> bound_0,
             std::tuple<Lower_1, Upper_1> bound_1, std::integer_sequence<int, First, Second>)
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

            return DiceForge::integrals(F1, evaluate(bound_1, v0));
        };

        return DiceForge::integrals(F0, bound_0);
    }

}
