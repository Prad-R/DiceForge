#include "XORShift.h"

namespace DiceForge
{
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

    template class XORShift<uint32_t>;
    template class XORShift<uint64_t>;
}