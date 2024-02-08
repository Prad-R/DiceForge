#include "naor_reingold.h"

// Refer wikipedia article for these numbers and their explanation
static constexpr int l = 4999583;
static constexpr int p = 4999583 * 2 - 1;
static constexpr int g = 40801;
static constexpr int a[] = {9155,  37223, 25630, 28608, 5688,  38638, 37876,
                            27155, 28658, 3774,  31886, 31849, 26165, 23774,
                            38839, 29341, 5139,  18043, 27840, 34032, 24816,
                            9013,  4974,  9388,  3885,  5250,  10898, 37617,
                            33660, 11963, 27934, 27012, 23453};
// Precalculated exponents and remainders
static constexpr long long remainders[] = {
    1267111, 8353111, 283306,  9369121, 6937186, 1956661, 5787406,
    5938426, 763216,  9070396, 9323026, 6913231, 5137681, 3559396,
    1554361, 8057161, 9273391, 2649556, 5296831, 7695076, 8522941,
    8970046, 9272356, 9997441, 1938661, 6885946, 6206236, 4360726,
    6437311, 2713576, 8124781, 2524471, 412321};

// Setting a default seed
NaorReingold::NaorReingold() { seed = 1234; }

NaorReingold &NaorReingold::get() {
  static NaorReingold instance;
  return instance;
}

void NaorReingold::set_seed(int seed) { get().p_set_seed(seed); }
int NaorReingold::generate() { return get().p_generate(); }

void NaorReingold::p_set_seed(int p_seed) { seed = p_seed; }

int NaorReingold::p_generate() {
  long long res = remainders[0];
  for (int i = 0; i < 32; i++) {
    // Only multiply the remainder if the corresponding bit is 1
    int to_multiply = seed & (1 << i);

    if (to_multiply)
      res = (res * remainders[i + 1]) % p;
  }

  seed = res;
  return res;
}
