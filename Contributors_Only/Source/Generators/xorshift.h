#pragma once
#include <math.h>
#include <type_traits>

#ifndef DF_XORSHIFT_H
#define DF_XORSHIFT_H

#include "generator.h"

namespace DiceForge
{   
    /* DiceForge::XORShift - A RNG utilizing Marsgalia's XORShift algorithm 
    * Supports 32 and 64 bit unsigned integers */
    template <typename T>
    class XORShift : public Generator<T>
    {
    private:
        T m_state;
        T generate() override;
        void reseed(T seed) override;
    public:
        XORShift(T seed);
        ~XORShift();
    };

    template <typename T>
    XORShift<T>::XORShift(T seed)
        : m_state(seed)
    {
    }

    template <typename T>
    XORShift<T>::~XORShift()
    {
    }

    template <typename T>
    void XORShift<T>::reseed(T seed)
    {
        m_state = seed;
    }

    template <>
    uint32_t XORShift<uint32_t>::generate()
    {
        m_state ^= m_state << 13;
        m_state ^= m_state >> 17;
        m_state ^= m_state << 5;
        return m_state;
    }

    template <>
    uint64_t XORShift<uint64_t>::generate()
    {
        m_state ^= m_state << 13;
        m_state ^= m_state >> 7;
        m_state ^= m_state << 17;
        return m_state;
    }

    typedef XORShift<uint32_t> XORShift32;
    typedef XORShift<uint64_t> XORShift64;
}

#endif
