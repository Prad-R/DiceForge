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
            inline void propagate();

            /**
             * @brief generate - Generates a random number using the Blum-Blum-Shub algorithm
             * @return T - The generated random number
             */
            T generate() override;

            /**
             * @brief check_seed - Checks if the seed is coprime with n (p*q)
             * @param seed - The seed value
             */
            void check_seed(T seed);

            /**
             * @brief reseed - Reseeds the generator with a new seed
             * @param seed - The new seed value
             */
            void reseed(T seed) override;

        public:
            /**
             * @brief Constructor for BlumBlumShub
             * @param seed - The initial seed value
             */
            BlumBlumShub(T seed);

            /**
             * @brief Destructor for BlumBlumShub
             */
            ~BlumBlumShub();
    };

    // Typedefs for convenience
    typedef BlumBlumShub<uint32_t> BlumBlumShub32;
    typedef BlumBlumShub<uint64_t> BlumBlumShub64;
}

#endif