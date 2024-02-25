#ifndef DF_XORSHIFT_H
#define DF_XORSHIFT_H

#include "generator.h"

namespace DiceForge
{   
    /// @brief DiceForge::XORShift - A PRNG following the XORShift* algorithm
    /// A naive implementation of the original XORShift algorithm proposed by Marsaglia
    /// followed by a multiplicative transform
    /// @note Currently 32-bit and 64-bit variants of the PRNG are supported
    /// @tparam T Datatype of the result
    template <typename T>
    class XORShift : public Generator<T>
    {
    private:
        T m_state;
        T generate() override;
        void reseed(T seed) override;
    public:
        /// @brief Initializes the XOR Shift RNG with the specified seed
        /// @param seed must be a non-zero number
        /// @note If the given seed is zero, then the current system 
        XORShift(T seed);
        ~XORShift();
    };

    typedef XORShift<uint32_t> XORShift32;
    typedef XORShift<uint64_t> XORShift64;
}

#endif
