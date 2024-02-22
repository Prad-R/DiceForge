#ifndef DICEFORGE_LFSR_H
#define DICEFORGE_LFSR_H

#include "generator.h"

namespace DiceForge {
    class LFSR : public DiceForge::Generator<long long int> {
        private:
            long long int curr_seed = 0;
            long long int generate() override;
            void reseed(long long int seed) override;
    };
}


#endif //DICEFORGE_LFSR_H
