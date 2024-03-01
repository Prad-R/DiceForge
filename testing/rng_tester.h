#ifndef RNG_TESTER_H
#define RNG_TESTER_H

#include "diceforge_generators.h"

#include <chrono>
#include <vector>

/// @brief test_scatter - generates data for a scatter plot
/// @param G random number generator to be tested
/// @param count number of random numbers to be generated for testing 
/// @return a vector containing the i th generated random number as the i the elemnent
template <typename T>
std::vector<size_t> test_scatter(DiceForge::Generator<T>& G, int count)
{
    std::vector<T> s;
    s.reserve(count);
    for (int i = 0; i < count; i++)
    {
        s.emplace_back(G.next());
    }
    return s;
}

/// @brief test_mod_frequency - function to generate a frequency distribution of residues of random number generated modulo x
/// @param G random number generator to be tested
/// @param count number of random numbers to be generated for testing 
/// @param x residue modulo x
/// @return the frequency distribution
template <typename T>
std::vector<int> test_mod_frequency(DiceForge::Generator<T>& G, int count, int x)
{
    std::vector<int> s;
    s.reserve(x);
    for (int i = 0; i < count; i++)
    {
        s[G.next_in_range(0, x-1)]++;
    }
    return s;
}

/// @brief test_bin_frequency - it scales the unit random real generated [0, 1) by the RNG to [0, bins) and creates a frequency distribution of
/// the closest integer that the generated number is to
/// @param G random number generator to be tested
/// @param count number of random numbers to be generated for testing 
/// @param bins number 
/// @return the frequency distribution
template <typename T>
std::vector<int> test_bin_frequency(DiceForge::Generator<T>& G, int count, int bins)
{
    std::vector<int> s;
    s.reserve(bins);
    for (int i = 0; i < count; i++)
    {
        s[floor(G.next_in_crange(0.0, bins+1))]++;
    }
    return s;
}
/// @brief test_statistical - a function to generate the mean, variance, minimum and maximum of the RNG when generating unit random reals in [0, 1)
/// @param G random number generator to be tested
/// @param count number of random numbers to be generated for testing 
/// @return a vector containing {mean, variance, minimum, maximum}
template <typename T>
std::vector<double> test_statistical(DiceForge::Generator<T>& G, int count)
{
    std::vector<double> s;
    s.reserve(count);
    for (int i = 0; i < count; i++)
    {
        s.emplace_back(G.next_unit());
    }
    
    double x = 0, x2 = 0, min = 1, max = 0;
    for (int i = 0; i < count; i++)
    {
        x += s[i];
        x2 += s[i] * s[i];

        if (s[i] < min) min = s[i];
        if (s[i] > max) max = s[i];
    }

    std::vector<double> stat_data = {0,0,0,0};   // mean, variance, minimum, maximum

    stat_data[0] = x/count;
    stat_data[1] = x2/count - (x/count) * (x/count);
    stat_data[2] = min;
    stat_data[3] = max;

    return stat_data;
}

/// @brief test_time - calculates the time taken by the RNG to generate the specified count of integers
/// @param G random number generator to be tested
/// @param count number of random integers to be generated 
/// @return time taken to generate the numbers in milliseconds
template <typename T>
double test_time_integers(DiceForge::Generator<T>& G, int count)
{
    std::chrono::time_point start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < count; i++)
    {
        G.next();
    }    

    std::chrono::time_point end = std::chrono::high_resolution_clock::now();

    return (end - start).count() * 1e-6;
}

/// @brief test_time_floats - calculates the time taken by the RNG to generate the specified count of floats
/// @param G random number generator to be tested
/// @param count number of random floats to be generated 
/// @return time taken to generate the numbers in milliseconds
template <typename T>
double test_time_floats(DiceForge::Generator<T>& G, int count)
{
    std::chrono::time_point start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < count; i++)
    {
        G.next_unit();
    }    

    std::chrono::time_point end = std::chrono::high_resolution_clock::now();

    return (end - start).count() * 1e-6;
}

#endif 
