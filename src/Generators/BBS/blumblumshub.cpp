#include "blumblumshub.h"
#include <numeric>

namespace DiceForge
{
    inline void BlumBlumShub32::propagate(){
        state = (state * state) % n;

        // Ensure the state is not 0 or 1
        if(state == 0 || state == 1){
            state += 429496737ULL; // A random constant to avoid getting stuck at 0 or 1
        }
    }

    BlumBlumShub32::BlumBlumShub32(uint32_t seed){
        reseed(seed);
    }

    uint32_t BlumBlumShub32::generate() {
        uint32_t num = 0;
        for(int i = 0; i < 32; i++){
            propagate();
            num = (num << 1) | (state % 2); // Extracting LSB and appending
        }
        return num;
    }

    void BlumBlumShub32::reseed(uint32_t seed) {
        if (std::gcd(seed, n) != 1){
            seed += 429496737ULL;
        }
        state = seed % n;
    }

    inline void BlumBlumShub64::propagate(){
        state = (state * state) % n;

        // Ensure the state is not 0 or 1
        if(state == 0 || state == 1){
            state += 429496737ULL; // A random constant to avoid getting stuck at 0 or 1
        }
    }

    BlumBlumShub64::BlumBlumShub64(uint64_t seed){
        reseed(seed);
    }

    uint64_t BlumBlumShub64::generate() {
        uint64_t num = 0;
        for(int i = 0; i < 64; i++){
            propagate();
            num = (num << 1) | (state % 2); // Extracting LSB and appending
        }
        return num;
    }

    void BlumBlumShub64::reseed(uint64_t seed) {
        if (std::gcd(seed, n) != 1){
            seed += 429496737ULL;
        }
        state = seed % n;
    }
}