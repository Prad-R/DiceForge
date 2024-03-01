#ifndef DF_NAOR_REINGOLD_H
#define DF_NAOR_REINGOLD_H
#include "generator.h"

namespace DiceForge {
  
  /// @brief DiceForge::NaorReingold - An implementation of the Naor-Reingold PRF 
  /// for generating 32-bit unsigned integers
  class NaorReingold : public Generator<uint32_t> {
    private:
      uint32_t m_state;   // Internal state
      uint32_t generate() override;
      void reseed(uint32_t seed) override;
      
    public:
      /// @brief Initializes the PRF with the given seed
      /// @param seed seed to initialize the PRF with
      /// @note The key for the PRF is predetermined and fixed. The seed is not the key.
      NaorReingold(uint32_t seed);
      /// @brief Default destructor
      ~NaorReingold() = default;
};

  typedef NaorReingold NaorReingold32;
} // namespace DiceForge

#endif
