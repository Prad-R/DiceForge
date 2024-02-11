#ifndef DF_BLUMBLUMSHUB_H
#define DF_BLUMBLUMSHUB_H

#include "generator.h"
#include "cmath"

namespace DiceForge
{   
    /* DiceForge::BlumBlumShub - A RNG utilizing the Blum-Blum-Shub algorithm
    * Supports 32 and 64 bit unsigned integers */
    template <typename T>
    class BlumBlumShub : public Generator<T>
    {
        static_assert(std::is_unsigned<T>::value, "T must be an unsigned type");
    
        private:
            T state;

            static const uint64_t p = 491;
            static const uint64_t q = 503;
            static const uint64_t n = p * q;

            T generate override()
            {
                // state = (state * state) % n;
                state = (state * state) % n;
                return state;
            }

            bool check_seed(T seed){
                if(seed == 1 || seed == 0 || gcd(seed, n) != 1){
                    return false;
                }
                return true;
            }

            template <typename T>
            void reseed(T seed) override{
                state = seed;
            }
        
        public:
            template <typename T>
            BlumBlumShub(T seed) : state(seed) {}

            template <typename T>
            BlumBlumShub<T>::~BlumBlumShub() {}
    };

    typedef BlumBlumShub<uint32_t> BlumBlumShub32;
    typedef BlumBlumShub<uint64_t> BlumBlumShub64;
}

#endif