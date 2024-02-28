#ifndef NAOR_REINGOLD_H
#define NAOR_REINGOLD_H
#include "../generator.h"

namespace DiceForge {
template <typename T> class NaorReingold : public Generator<T> {
private:
  T m_state;
  T generate() override;
  void reseed(T seed) override;

public:
  NaorReingold(T seed);
  ~NaorReingold();
};

typedef NaorReingold<uint32_t> NaorReingold32;
} // namespace DiceForge

#endif
