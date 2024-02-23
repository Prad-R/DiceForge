#ifndef DICEFORGE_LFSR_H
#define DICEFORGE_LFSR_H

#include "generator.h"

namespace DiceForge {
    class LFSR : public DiceForge::Generator<unsigned long long int> {
        private:
            unsigned long long int curr_seed = 0;
            unsigned long long int generate() override;
            void reseed(unsigned long long int seed) override;
    };
}


#endif
