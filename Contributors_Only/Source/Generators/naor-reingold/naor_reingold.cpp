#include "./naor_reingold.h"
typedef unsigned int uint32_t;

// Refer wikipedia article for these numbers and their explanation
static constexpr uint32_t l = 9999929;
static constexpr uint32_t p = 4279969613;
static constexpr uint32_t g = 9999918;
static constexpr uint32_t a[] = {
    650051,  3948705, 3142325, 4036110, 1141941, 5739231, 5725758,
    8299330, 1776388, 1423550, 9260804, 156410,  1190436, 61218,
    2382500, 1738876, 7978879, 6010478, 310917,  4280253, 24724,
    7087659, 796099,  8383655, 7638286, 1390415, 7899225, 5628976,
    1472292, 4284966, 9708041, 4179835, 3635954};

// Precalculated exponents and remainders (i.e. g ^ a[i] % p)
static constexpr uint32_t remainders[] = {
    2737981618, 1080320388, 1723072060, 4228301455, 4149129801, 3571453456,
    2502499170, 2645177746, 1174113779, 460790047,  2432060459, 3642283025,
    2171537408, 1964923279, 167928637,  764994146,  33580906,   152749582,
    3155509836, 1068833496, 3292407144, 686219412,  550755449,  1072869831,
    2507702675, 2920217274, 2456957004, 3987169726, 3828720855, 2539518588,
    420287618,  2009403111, 1732156098};

namespace DiceForge {
template <typename T> NaorReingold<T>::NaorReingold(T seed) : m_state(seed) {}

template <typename T> NaorReingold<T>::~NaorReingold() = default;

template <typename T> void NaorReingold<T>::reseed(T seed) { m_state = seed; }

template <> uint32_t NaorReingold<uint32_t>::generate() {
  uint32_t res = remainders[0];
  for (int i = 0; i < 32; i++) {
    // Only multiply the remainder if the corresponding bit is 1
    bool to_multiply = m_state & (1 << i);

    if (to_multiply)
      res = (res * remainders[i + 1]) % p;
  }

  m_state = res;
  return res;
}

template class NaorReingold<uint32_t>;

} // namespace DiceForge
