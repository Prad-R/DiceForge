#pragma once
#include <math.h>
#include <type_traits>

namespace DiceForge
{   
    /* DiceForge::XORShift - A RNG utilizing the XORShift algorithm 
    * Supports 32 and 64 bit unsigned integers */
    template <typename T>
    class XORShift
    {
    private:
        T m_state;
    public:
        /* XORShift(uint32/uint64 seed) - sets up the RNG with 'seed' as the inital state */
        XORShift(T seed);
        /* ~XORShift() - default destructor */
        ~XORShift();   
        /* uint32/uint64 XORShift::next() - returns the next generated random number */                     
        T next() const;
    };

    typedef XORShift<u_int32_t> XORShift32;      // A 32-bit XORShift RNG
    typedef XORShift<u_int64_t> XORShift64;      // A 64-bit XORShift RNG

    template <typename T>
    inline XORShift<T>::XORShift(T seed)
        : m_state(seed)
    {
    }
    
    template <typename T>
    inline XORShift<T>::~XORShift()
    {
    }

    template <typename T>
    inline T XORShift<T>::next() const
    {
        if constexpr (std::is_same<T, int>)
        {
            m_state ^= m_state << 13;
            m_state ^= m_state >> 17;
            m_state ^= m_state << 5;
        }
        else if constexpr (std::is_same<T, long>)
        {
            m_state ^= m_state << 13;
            m_state ^= m_state >> 7;
            m_state ^= m_state << 17;
        }

        return m_state;
    }

    /* Can be implemented - xorshiro, xorshift+ */
}