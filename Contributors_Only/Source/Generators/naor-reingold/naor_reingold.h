#ifndef NAOR_REINGOLD_H
#define NAOR_REINGOLD_H
#include "generator.h"

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

#endif
