/***MERSENNE TWISTER PRNG***/
/*generates 64 bit integers*/
/*Parameters involved
(w,n,m,r)=(64,312,156,31)
*/

#ifndef DF_MT_H
#define DF_MT_H

#include "generator.h"

namespace DiceForge{

    /// @brief DiceForge::MT32 - A Mersenne Twister RNG for generating 32-bit unsigned integers
    class MT32 : public Generator<uint32_t>
    {
    private:
        // Main Parameters:
        int N;                          // length of state value vector
        int M;                          // optimum value as mid
        uint32_t A;                     // vector in the matrix A
        uint32_t upperbits, lowerbits;  // for obtaining first w-r bits of the number
        // Tempering Parameters:
        uint32_t tempering_mask_B;
        uint32_t tempering_mask_C;
        uint32_t tempering_shift_U;
        uint32_t tempering_shift_S;
        uint32_t tempering_shift_T;
        uint32_t tempering_shift_L;
        // Other Parameters:
        std::vector<uint32_t> mt;       // State Vector
        int mti = N + 1;                // Used as index for the array MT.
        uint32_t seed;                  // Seed given from main
        // Funtcions to generate first N pseudo-random numbers as a seed for the algorithm.
        void sgenrand(uint32_t);
        void trytransform();
        uint32_t temper(uint32_t);
        uint32_t generate() override;
        void reseed(uint32_t seed) override;
    public:
        /// @brief Initializes the Mersenne Twister RNG with the specified seed
        /// @param seed seed to initialize the RNG with
        MT32(uint32_t seed);
        ~MT32() = default;
    };
    
    /// @brief DiceForge::MT64 - A Mersenne Twister RNG for generating 64-bit unsigned integers
    class MT64 : public Generator<uint64_t>
    {
    private:
        // Main Parameters:
        int N;                          // length of state value vector
        int M;                          // optimum value as mid
        uint64_t A;                     // vector in the matrix A
        uint64_t upperbits, lowerbits;  // for obtaining first w-r bits of the number
        // Tempering Parameters:
        uint64_t tempering_mask_B;
        uint64_t tempering_mask_C;
        uint64_t tempering_shift_U;
        uint64_t tempering_shift_S;
        uint64_t tempering_shift_T;
        uint64_t tempering_shift_L;
        // Other Parameters:
        std::vector<uint64_t> mt;       // State Vector
        int mti = N + 1;                // Used as index for the array MT.
        uint64_t seed;                  // Seed given from main
        // Funtcions to generate first N pseudo-random numbers as a seed for the algorithm.
        void sgenrand(uint64_t);
        void trytransform();
        uint64_t temper(uint64_t);
        uint64_t generate() override;
        void reseed(uint64_t seed) override;
    public:
        /// @brief Initializes the Mersenne Twister RNG with the specified seed
        /// @param seed seed to initialize the RNG with
        MT64(uint64_t seed);
        ~MT64() = default;
    };
    
    // Typedef for convenience
    
    typedef MT64 MT;
}

#endif