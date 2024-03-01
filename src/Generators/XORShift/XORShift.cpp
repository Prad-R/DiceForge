#include "XORShift.h"
#include <chrono>

namespace DiceForge
{
    XORShift32::XORShift32(uint32_t seed)
    {
        reseed(seed);
    }

    void XORShift32::reseed(uint32_t seed)
    {
        if (seed == 0){
            m_state = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        }
        else {
            m_state = seed;
        }
    }

    uint32_t XORShift32::generate()
    {
        m_state ^= m_state << 13;
        m_state ^= m_state >> 17;
        m_state ^= m_state << 5;
        return m_state * 0x2545F4914F6CDD1DULL;
    }

    XORShift64::XORShift64(uint64_t seed)
    {
        reseed(seed);
    }

    void XORShift64::reseed(uint64_t seed)
    {
        if (seed == 0){
            m_state = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        }
        else {
            m_state = seed;
        }
    }

    uint64_t XORShift64::generate()
    {
        m_state ^= m_state << 13;
        m_state ^= m_state >> 7;
        m_state ^= m_state << 17;
        return m_state * 0x2545F4914F6CDD1DULL;
    }
}