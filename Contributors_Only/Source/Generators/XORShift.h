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

    typedef XORShift<uint32_t> XORShift32;
    typedef XORShift<uint64_t> XORShift64;
}

#endif
