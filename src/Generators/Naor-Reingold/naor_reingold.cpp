
#include "naor_reingold.h"
#include <chrono>

typedef unsigned long long ull;
typedef unsigned int uint32_t;

// Refer wikipedia article for these numbers and their explanation
static constexpr ull l = 9999929;
static constexpr ull p = 4279969613;
static constexpr ull g = 9999918;
static constexpr ull a[] = {
    650051,  3948705, 3142325, 4036110, 1141941, 5739231, 5725758,
    8299330, 1776388, 1423550, 9260804, 156410,  1190436, 61218,
    2382500, 1738876, 7978879, 6010478, 310917,  4280253, 24724,
    7087659, 796099,  8383655, 7638286, 1390415, 7899225, 5628976,
    1472292, 4284966, 9708041, 4179835, 3635954};

namespace DiceForge {

  ull power(ull a, ull b, ull mod) {
    ull result = 1;
    ull a_pwr = a % mod;
    while (b) {
      if (b % 2 == 1)
        result *= a_pwr;
      a_pwr *= a_pwr;
      a_pwr %= mod; // Take modulo everywhere
      result %= mod;
      b /= 2;
    }
    return result;
  }

  NaorReingold::NaorReingold(uint32_t seed) {
    if (seed == 0)
      m_state = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    else
      m_state = seed;
  }

  void NaorReingold::reseed(uint32_t seed) { 
    if (seed == 0)
      m_state = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    else
      m_state = seed;
  }

  uint32_t NaorReingold::generate() {
    ull res = 1;
    for (int i = 0; i < 32; i++) {
      // Only multiply the remainder if the corresponding bit is 1
      bool to_multiply = m_state & (1 << i);

      if (to_multiply)
        res = (res * power(g, a[i], p)) % p;
    }

    m_state++;
    return res;
  }

} // namespace DiceForge
