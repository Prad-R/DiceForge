#ifndef DF_XORSHIFT_H
#define DF_XORSHIFT_H

#include "generator.h"

namespace DiceForge
{   
    /// @brief DiceForge::XORShift32 - A PRNG following the XORShift* algorithm
    /// A naive implementation of the original XORShift algorithm proposed by Marsaglia
    /// followed by a multiplicative transform
    /// @note Generates 32-bit unsigned integers
    class XORShift32 : public Generator<uint32_t>
    {
    private:
        uint32_t m_state;   // Internal state
        uint32_t generate() override;
        void reseed(uint32_t seed) override;
    public:
        /// @brief Initializes the XOR Shift RNG with the specified seed
        /// @param seed must be a non-zero number
        /// @note If the given seed is zero, then the current system is used as the seed
        XORShift32(uint32_t seed);
        /// @brief Default destructor
        ~XORShift32() = default;
    };

    /// @brief DiceForge::XORShift64 - A PRNG following the XORShift* algorithm
    /// A naive implementation of the original XORShift algorithm proposed by Marsaglia
    /// followed by a multiplicative transform
    /// @note Generates 64-bit unsigned integers
    class XORShift64 : public Generator<uint64_t>
    {
    private:
        uint64_t m_state;   // Internal state
        uint64_t generate() override;
        void reseed(uint64_t seed) override;
    public:
        /// @brief Initializes the XOR Shift RNG with the specified seed
        /// @param seed must be a non-zero number
        /// @note If the given seed is zero, then the current system is used as the seed
        XORShift64(uint64_t seed);
        /// @brief Default destructor
        ~XORShift64() = default;
    };

    typedef XORShift64 XORShift;
}

#endif
