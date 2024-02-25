#ifndef DICEFORGE_LFSR_H
#define DICEFORGE_LFSR_H

#include "generator.h"

namespace DiceForge {
    // Linear Feedback Shift Register class (derived from Generator)
    class LFSR : public DiceForge::Generator<unsigned long long int> {
        private:
            // Two curr_seeds, together forming a 128-bit seed
            unsigned long long int curr_seed1 = 0, curr_seed2 = 0;
            // Function to generate a random 64-bit positive integer
            unsigned long long int generate() override;
            // Function to reseed the RNG
            void reseed(unsigned long long int seed) override;
    };
}


#endif
