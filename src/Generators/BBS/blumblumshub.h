#ifndef DF_BLUMBLUMSHUB_H
#define DF_BLUMBLUMSHUB_H

#include "generator.h"
#include "bigint.h"

namespace DiceForge
{
    /**
     * @brief DiceForge::BlumBlumShub32 - A RNG utilizing the Blum-Blum-Shub algorithm
     * for generating 32-bit unsigned random integers
     */
    class BlumBlumShub32 : public Generator<uint32_t>
    {
        private:
            static const uint64_t p;
            static const uint64_t q;
            static const uint64_t n;

            BigInt128 state; // Internal state

            /**
             * @brief propagate - Advances the internal state using the Blum-Blum-Shub algorithm
             */
            inline void propagate();

            /**
             * @brief generate - Generates a random number using the Blum-Blum-Shub algorithm
             * @return The generated random number
             */
            uint32_t generate() override;

            /**
             * @brief reseed - Reseeds the generator with a new seed
             * @param seed The new seed value
             * @note if the seed is zero then a non-zero seed is adopted by default
             */
            void reseed(uint32_t seed) override;

        public:
            /**
             * @brief Constructor for BlumBlumShub32
             * @param seed The initial seed value
             * @note if the seed is zero then a non-zero seed is adopted by default
             */
            BlumBlumShub32(uint32_t seed);

            /**
             * @brief Destructor for BlumBlumShub32
             */
            ~BlumBlumShub32() = default;
    };

    /**
     * @brief DiceForge::BlumBlumShub64 - A RNG utilizing the Blum-Blum-Shub algorithm
     * for generating 64-bit unsigned random integers
     */
    class BlumBlumShub64 : public Generator<uint64_t>
    {
        private:
            static const uint64_t p;
            static const uint64_t q;
            static const uint64_t n;

            BigInt128 state; // Internal state

            /**
             * @brief propagate - Advances the internal state using the Blum-Blum-Shub algorithm
             */
            inline void propagate();

            /**
             * @brief generate - Generates a random number using the Blum-Blum-Shub algorithm
             * @return The generated random number
             */
            uint64_t generate() override;

            /**
             * @brief reseed - Reseeds the generator with a new seed
             * @param seed The new seed value
             * @note if the seed is zero then a non-zero seed is adopted by default
             */
            void reseed(uint64_t seed) override;

        public:
            /**
             * @brief Constructor for BlumBlumShub64
             * @param seed The initial seed value
             * @note if the seed is zero then a non-zero seed is adopted by default
             */
            BlumBlumShub64(uint64_t seed);

            /**
             * @brief Destructor for BlumBlumShub64
             */
            ~BlumBlumShub64() = default;
    };

    // Typedef for convenience

    typedef BlumBlumShub64 BlumBlumShub;
}

#endif