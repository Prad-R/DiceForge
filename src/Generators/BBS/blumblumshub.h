#ifndef DF_BLUMBLUMSHUB_H
#define DF_BLUMBLUMSHUB_H

#include "generator.h"

namespace DiceForge
{
    /**
     * @brief DiceForge::BlumBlumShub32 - A RNG utilizing the Blum-Blum-Shub algorithm
     * for generating 32-bit unsigned random integers
     */
    class BlumBlumShub32 : public Generator<uint32_t>
    {
        private:
            static const uint64_t p = 60539;
            static const uint64_t q = 50147;
            static const uint64_t n = p * q;

            uint64_t state; // Internal state

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
             * @brief check_seed - Checks if the seed is coprime with n (p*q)
             * @note If it is not then a constant is added to the seed to make it coprime
             * @param seed The seed value
             */
            void check_seed(uint32_t& seed);

            /**
             * @brief reseed - Reseeds the generator with a new seed
             * @param seed The new seed value
             */
            void reseed(uint32_t seed) override;

        public:
            /**
             * @brief Constructor for BlumBlumShub32
             * @param seed The initial seed value
             */
            BlumBlumShub32(uint32_t seed){
                check_seed(seed);
            }

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
            static const uint64_t p = 60539;
            static const uint64_t q = 50147;
            static const uint64_t n = p * q;

            uint64_t state; // Internal state

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
             * @brief check_seed - Checks if the seed is coprime with n (p*q)
             * @note If it is not then a constant is added to the seed to make it coprime
             * @param seed The seed value
             */
            void check_seed(uint64_t& seed);

            /**
             * @brief reseed - Reseeds the generator with a new seed
             * @param seed The new seed value
             */
            void reseed(uint64_t seed) override;

        public:
            /**
             * @brief Constructor for BlumBlumShub64
             * @param seed The initial seed value
             */
            BlumBlumShub64(uint64_t seed){
                check_seed(seed);
            }

            /**
             * @brief Destructor for BlumBlumShub64
             */
            ~BlumBlumShub64() = default;
    };

    // Typedef for convenience

    typedef BlumBlumShub64 BlumBlumShub;
}

#endif