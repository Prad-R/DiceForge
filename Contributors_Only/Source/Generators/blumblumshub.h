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
            static const uint64_t p = 60539;
            static const uint64_t q = 50147;
            static const uint64_t n = p * q;

            uint64_t state;
            int _genlen;

            inline void propagate(){
                state = (state * state) % n;
                if(state == 0 || state == 1){
                    state += 4294967387ULL;
                }
            }

            T generate() override {
                T num = 0;
                for(int i = 0; i < _genlen; i++){
                    propagate();
                    num = (num << 1) | (state%2);
                }
                return num;
            }

            bool check_seed(T seed){
                if(seed == 1 || seed == 0 || gcd(seed, n) != 1){
                    return false;
                }
                return true;
            }

            void reseed(T seed) override{
                state = seed;
            }
        
        public:
            BlumBlumShub(T seed) : state(seed) {
                _genlen = sizeof(T)*8;
            }

            ~BlumBlumShub() {}
    };

    typedef BlumBlumShub<uint32_t> BlumBlumShub32;
    typedef BlumBlumShub<uint64_t> BlumBlumShub64;
}

#endif