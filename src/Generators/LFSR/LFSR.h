#ifndef DF_LFSR_H
#define DF_LFSR_H

#include "generator.h"

namespace DiceForge {
    /// @brief DiceForge::LFSR64 - Linear Feedback Shift Register class (derived from Generator)
    /// for generating 64-bit unsigned integers
    class LFSR64 : public DiceForge::Generator<uint64_t> {
    private:
        // Two curr_seeds, together forming a 128-bit seed
        uint64_t curr_seed1 = 0, curr_seed2 = 0;
        // Function to generate a random 64-bit positive integer
        uint64_t generate() override;
        // Function to reseed the RNG
        void reseed(uint64_t seed) override;
    public:
        /// @brief Initializes the LFSR with the specified seed
        /// @param seed seed to initialize the RNG with
        /// @note if the seed provided is zero, then the current system time is taken as seed
        LFSR64(uint64_t seed);
        /// @brief Default destructor
        ~LFSR64() = default;
    };

    /// @brief DiceForge::LFSR32 - Linear Feedback Shift Register class (derived from Generator)
    /// for generating 32-bit unsigned integers
    class LFSR32 : public DiceForge::Generator<uint32_t> {
    private:
        // Two curr_seeds, together forming a 128-bit seed
        uint64_t curr_seed1 = 0, curr_seed2 = 0;
        // Function to generate a random 32-bit positive integer
        uint32_t generate() override;
        /// @brief Function to reseed the RNG
        /// @note if the seed provided is zero, then the current system time is taken as seed
        void reseed(uint32_t seed) override;
    public:    
        /// @brief Initializes the LFSR with the specified seed
        /// @param seed seed to initialize the RNG with
        /// @note if the seed provided is zero, then the current system time is taken as seed
        LFSR32(uint32_t seed);
        /// @brief Default destructor
        ~LFSR32() = default;
    };

    // Typedef for convenience

    typedef LFSR64 LFSR;
}


#endif
