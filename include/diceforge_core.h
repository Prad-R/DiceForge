#ifndef DF_CORE_H
#define DF_CORE_H

#include <limits>
#include <iostream>
#include <algorithm>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>

namespace DiceForge
{
#if defined(___linux__)

    typedef int int32_t;           // A signed integer (32 bit)
    typedef __int64_t int64_t;     // A signed integer (64 bit)
    typedef unsigned int uint32_t; // An unsigned integer (32 bit)
    typedef __uint64_t uint64_t;   // An unsigned integer (64 bit)
    typedef __int128_t int128_t;   // A signed integer (128 bit)
    typedef __uint128_t uint128_t; // An unsigned integer (128 bit)

    typedef uint64_t uint_t; // An unsigned integer (64 bit)
    typedef int64_t int_t;   // A signed integer (64 bit)
    typedef double real_t;   // A signed floating point real number (64 bit)

#elif __APPLE__
    typedef int int32_t;                // A signed integer (32 bit)
    typedef long long int int64_t;           // A signed integer (64 bit)
    typedef unsigned int uint32_t;      // An unsigned integer (32 bit)
    typedef unsigned long long int uint64_t; // An unsigned integer (64 bit)
    typedef __int128_t int128_t;        // A signed integer (128 bit)
    typedef __uint128_t uint128_t;      // An unsigned integer (128 bit)

    typedef uint64_t uint_t; // An unsigned integer (64 bit)
    typedef int64_t int_t;   // A signed integer (64 bit)
    typedef double real_t;   // A signed floating point real number (64 bit)

#else

    typedef int int32_t;                     // A signed integer (32 bit)
    typedef long long int int64_t;           // A signed integer (64 bit)
    typedef unsigned int uint32_t;           // An unsigned integer (32 bit)
    typedef unsigned long long int uint64_t; // An unsigned integer (64 bit)
    typedef __int128_t int128_t;             // A signed integer (128 bit)
    typedef __uint128_t uint128_t;           // An unsigned integer (128 bit)

    typedef uint64_t uint_t; // An unsigned integer (64 bit)
    typedef int64_t int_t;   // A signed integer (64 bit)
    typedef double real_t;   // A signed floating point real number (64 bit)

#endif

    /// @brief DiceForge::Generator<T> - A generic class for RNGs
    /// @tparam T datatype of random number generated (RNG implementation specific)
    /// @note Every RNG implemented in DiceForge is derived from this base class.
    /// @note For writing your own RNG it is advisable to use this as the base class for compatibility with other features.
    template <typename T>
    class Generator
    {
    public:
        /// @brief Returns a random integer generated by the RNG
        /// @returns An unsigned integer (usually 32 or 64 bit)
        T next()
        {
            return generate();
        };
        /// @brief Returns a random real between 0 and 1
        /// @returns An floating-point real number (64 bit)
        real_t next_unit()
        {
            real_t x = 1.0;
            while (x == 1.0) {
                x = generate() / real_t(std::numeric_limits<T>().max());
            }
            return x;
        }
        /// @brief Returns a random integer in the specified range
        /// @param min minimum value of the random number (inclusive)
        /// @param max maximum value of the random number (inclusive)
        /// @returns An signed integer (64 bit)
        int64_t next_in_range(T min, T max)
        {
            return (int64_t)floor(next_unit() * (max - min + 1)) + min;
        };
        /// @brief Returns a random real number in the specified range
        /// @param min minimum value of the random number
        /// @param max maximum value of the random number
        /// @returns An signed floating-point real number (64 bit)
        real_t next_in_crange(real_t min, real_t max)
        {
            real_t x = (real_t)max;
            while (x == max) {
                x = (max - min) * next_unit() + min;
            }
            return x;
        };
        /// @brief Re-initializes the RNG with specified seed
        /// @param seed seed provided for initialization
        void reset_seed(T seed)
        {
            reseed(seed);
        }

        /// @brief Returns a random element from the sequence
        /// @param first Iterator of first element (like .begin() of vectors)
        /// @param last Iterator after last element (like .end() of vectors)
        template <typename RandomAccessIterator>
        auto choice(RandomAccessIterator first, RandomAccessIterator last)
        {
            return *(first + next_in_range(0, last - first - 1));
        };

        /// @brief Returns a random element from the sequence
        /// @param first Iterator of first element (like .begin() of vectors)
        /// @param last Iterator after last element (like .end() of vectors)
        /// @param weights_first Iterator of first element of the weights list
        /// @param weights_last Iterator after last element of the weights list
        /// @note weights here refer to an array containing the probability weights for each element in the input sequence
        template <typename RandomAccessIterator1, typename RandomAccessIterator2>
        auto choice(RandomAccessIterator1 first, RandomAccessIterator1 last,
                    RandomAccessIterator2 weights_first, RandomAccessIterator2 weights_last)
        {
            if (last - first != weights_last - weights_first){
                throw std::invalid_argument("Lengths of sequence and weight sequence must be equal!");
            }
            else if (last == first){
                throw std::invalid_argument("Sequence must have non-zero length!");
            }
            auto cumulative_weights = (decltype(&(*weights_first)))malloc(sizeof(*weights_first) * (last - first));
            auto prev = *weights_first;
            prev = 0;
            for (auto it = weights_first; it != weights_last; it++){
                cumulative_weights[it - weights_first] = prev + *it;
                prev = cumulative_weights[it - weights_first];
            }
            auto ans = *(first + (std::upper_bound(cumulative_weights, &(cumulative_weights[last - first - 1]) + 1, next_unit() * cumulative_weights[last - first - 1]) - cumulative_weights));
            free(cumulative_weights);
            return ans;
        };

        /// @brief Shuffles the sequence in place
        /// @param first Iterator of first element (like .begin() of vectors)
        /// @param last Iterator after last element (like .end() of vectors)
        template <typename RandomAccessIterator>
        void shuffle(RandomAccessIterator first, RandomAccessIterator last)
        {
            auto temp = (decltype(&(*first)))malloc(sizeof(*first) * (last - first));
            for (auto it = first; it != last; it++){
                temp[it - first] = *it;
            }
            shuffle_array(temp, last - first);
            for (auto it = first; it!= last; it++){
                *it = temp[it - first];
            }
        };
        /*** Note: These are the only functions to be implemented by the implementation RNG ***/
    private:
        /// @brief Should return a random integer generated by the RNG
        virtual T generate() = 0;
        /// @brief Should initialize the seed for the RNG
        virtual void reseed(T seed) = 0;
        /// @brief Shuffles the array in place
        /// @param arr Pointer to the first element
        /// @param len Length of the array
        template <typename other_T>
        void shuffle_array(other_T arr[], T len) {
            T ind;
            std::vector<other_T> v;
            for (int i = 0; i < len; i++) {
                v.push_back(arr[i]);
            }
            for (int i = 0; i < len; i++) {
                ind = next_in_range(0, len - i - 1);
                arr[i] = v[ind];
                v.erase(v.begin() + ind);
            }
        };
    };

    /// @brief DiceForge::Continuous - A generic class for distributions describing continuous random variables
    class Continuous
    {
    public:
        /// @brief Returns the theoretical variance of the distribution
        virtual real_t variance() const = 0;
        /// @brief Returns the theoretical expectation value of the distribution
        virtual real_t expectation() const = 0;
        /// @brief Returns the minimum possible value of the random variable described by the distribution
        virtual real_t minValue() const = 0;
        /// @brief Returns the maximum possible value of the random variable described by the distribution
        virtual real_t maxValue() const = 0;
        /// @brief Probabiliity density function (pdf) of the distribution
        /// @param x location where the pdf is to be evaluated
        virtual real_t pdf(real_t x) const = 0;
        /// @brief Cumulative distribution function (cdf) of the distribution
        /// @param x location where the cdf is to be evaluated [P(X <= x)]
        virtual real_t cdf(real_t x) const = 0;
    };

    /// @brief DiceForge::Discrete - A generic class for distributions describing discrete random variables
    class Discrete
    {
    public:
        /// @brief Returns the theoretical variance of the distribution
        virtual real_t variance() const = 0;
        /// @brief Returns the theoretical expectation value of the distribution
        virtual real_t expectation() const = 0;
        /// @brief Returns the minimum possible value of the random variable described by the distribution
        virtual int_t minValue() const = 0;
        /// @brief Returns the maximum possible value of the random variable described by the distribution
        virtual int_t maxValue() const = 0;
        /// @brief Probabiliity mass function (pmf) of the distribution
        /// @param x location where the pdf is to be evaluated [P(X = x)]
        virtual real_t pmf(int_t x) const = 0;
        /// @brief Cumulative distribution function (cdf) of the distribution
        /// @param x location where the cdf is to be evaluated [P(X <= x)]
        virtual real_t cdf(int_t x) const = 0;
    };

    #if (__cplusplus >= 202002L)  // Atleast C++ 20 is required to use integration for 2D Random Variables

    /* Helper functions for integration of 2D PDF */

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

    #endif

}

#endif
