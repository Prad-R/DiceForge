#include "generator.h"

namespace DiceForge
{
    template <typename T>
    T Generator<T>::next()
    {
        return generate(); 
    };

    template <typename T>
    real_t Generator<T>::next_unit()
    {
        real_t x = 1.0;
        while (x == 1.0) {
            x = generate() / real_t(std::numeric_limits<T>().max());
        }
        return x;
    }

    template <typename T>
    int64_t Generator<T>::next_in_range(T min, T max)
    {
        return (int64_t)floor(next_unit() * (max - min + 1)) + min;
    };

    template <typename T>
    real_t Generator<T>::next_in_crange(real_t min, real_t max)
    {
        real_t x = (real_t)max;
        while (x == max) {
            x = (max - min) * next_unit() + min;
        }
        return x;
    };
    
    template <typename T>
    void Generator<T>::reset_seed(T seed)
    { 
        reseed(seed);
    }    
}