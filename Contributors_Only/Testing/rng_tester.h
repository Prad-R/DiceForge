#ifndef RNG_TESTER_H
#define RNG_TESTER_H

#include <vector>
#include "../Source/generators.h"

/* Needs documentation */

using namespace DiceForge;

template <typename T>
std::vector<size_t> test_scatter(Generator<T>& G, int count)
{
    std::vector<T> s;
    s.reserve(count);
    for (int i = 0; i < count; i++)
    {
        s.emplace_back(G.next());
    }
    return s;
}

template <typename T>
std::vector<size_t> test_mod_frequency(Generator<T>& G, int count, int mod)
{
    std::vector<size_t> s;
    s.reserve(mod);
    for (int i = 0; i < count; i++)
    {
        s[G.next_in_range(0, mod-1)]++;
    }
    return s;
}

template <typename T>
std::vector<size_t> test_bin_frequency(Generator<T>& G, int count, int bins)
{
    std::vector<size_t> s;
    s.reserve(bins);
    for (int i = 0; i < count; i++)
    {
        s[floor(G.next_in_crange(0.0, bins+1))]++;
    }
    return s;
}

template <typename T>
std::vector<real_t> test_statistical(Generator<T>& G, int count)
{
    std::vector<real_t> s;
    s.reserve(count);
    for (int i = 0; i < count; i++)
    {
        s.emplace_back(G.next_unit());
    }
    
    real_t x = 0, x2 = 0, min = 1, max = 0;
    for (int i = 0; i < count; i++)
    {
        x += s[i];
        x2 += s[i] * s[i];

        if (s[i] < min) min = s[i];
        if (s[i] > max) max = s[i];
    }

    std::vector<real_t> stat_data = {0,0,0,0};   // mean, variance, minimum, maximum

    stat_data[0] = x/count;
    stat_data[1] = x2/count - (x/count) * (x/count);
    stat_data[2] = min;
    stat_data[3] = max;

    return stat_data;
}

#endif 
