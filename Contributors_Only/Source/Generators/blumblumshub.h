#ifndef DF_BLUMBLUMSHUB_H
#define DF_BLUMBLUMSHUB_H

#include "generator.h"
#include <numeric>

namespace DiceForge
{
    /**
     * @brief DiceForge::BlumBlumShub - A RNG utilizing the Blum-Blum-Shub algorithm
     * Supports 32 and 64 bit unsigned integers
     */
    template <typename T>
    class BlumBlumShub : public Generator<T>
    {
        private:
            static const uint64_t p = 60539;
            static const uint64_t q = 50147;
            static const uint64_t n = p * q;

            uint64_t state; // Internal state
            int _genlen;    // Bit length for generation

            /**
             * @brief propagate - Advances the internal state using the Blum-Blum-Shub algorithm
             */
            inline void propagate(){
                state = (state * state) % n;

                // Ensure the state is not 0 or 1
                if(state == 0 || state == 1){
                    state += 4294967387ULL; // A random constant to avoid getting stuck at 0 or 1
                }
            }

            /**
             * @brief generate - Generates a random number using the Blum-Blum-Shub algorithm
             * @return T - The generated random number
             */
            T generate() override {
                T num = 0;
                for(int i = 0; i < _genlen; i++){
                    propagate();
                    num = (num << 1) | (state % 2); // Extracting LSB and appending
                }
                return num;
            }

            /**
             * @brief check_seed - Checks if the seed is coprime with n (p*q)
             * @param seed - The seed value
             */
            void check_seed(T seed){
                if (std::gcd(seed, n) != 1)
                {
                    std::cerr << "Error: Seed is not coprime with `n = p * q`" << std::endl;
                    exit(1);
                }
            }

            /**
             * @brief reseed - Reseeds the generator with a new seed
             * @param seed - The new seed value
             */
            void reseed(T seed) override{
                state = seed;
            }

        public:
            /**
             * @brief Constructor for BlumBlumShub
             * @param seed - The initial seed value
             */
            BlumBlumShub(T seed) : state(seed) {
                _genlen = sizeof(T) * 8; // Bit length for generation
                check_seed(seed);
            }

            /**
             * @brief Destructor for BlumBlumShub
             */
            ~BlumBlumShub() {}
    };

    // Typedefs for convenience
    typedef BlumBlumShub<uint32_t> BlumBlumShub32;
    typedef BlumBlumShub<uint64_t> BlumBlumShub64;
}

#endif