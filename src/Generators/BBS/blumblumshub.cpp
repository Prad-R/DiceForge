#include "blumblumshub.h"
#include <numeric>

namespace DiceForge
{
    const uint64_t BlumBlumShub32::p = 4294967291;
    const uint64_t BlumBlumShub32::q = 4294967279;
    const uint64_t BlumBlumShub32::n = BlumBlumShub32::p*BlumBlumShub32::q;

    const uint64_t BlumBlumShub64::p = 4294967291;
    const uint64_t BlumBlumShub64::q = 4294967279;
    const uint64_t BlumBlumShub64::n = BlumBlumShub64::p*BlumBlumShub64::q;

    inline void BlumBlumShub32::propagate(){
        state.square();
        state.mod(n);

        // Ensure the state is not 0 or 1
        if((state.data[0] == 0 || state.data[0] == 1)&& state.data[1] != 0){
            state.data[0] += 429496737ULL; // A random constant to avoid getting stuck at 0 or 1
            state.data[1] += state.data[0] >> 32;
            state.data[0] &= 0xFFFFFFFF;
        }
    }

    BlumBlumShub32::BlumBlumShub32(uint32_t seed): state(0, 0, 0, 0){
        reseed(seed);
    }

    uint32_t BlumBlumShub32::generate() {
        uint32_t num = 0;
        for(int i = 0; i < 4; i++){
            propagate();
            num = (num << 8) | (state.data[0] & 0xFF); // Extracting LSB and appending
        }
        return num;
    }

    void BlumBlumShub32::reseed(uint32_t seed) {
        for(int i = 1; i < 4; i++)
            state.data[i] = 0;
        state.data[0] = seed;
    }

    inline void BlumBlumShub64::propagate(){
        state.square();
        state.mod(n);

        // Ensure the state is not 0 or 1
        if((state.data[0] == 0 || state.data[0] == 1)&& state.data[1] != 0){
            state.data[0] += 429496737ULL; // A random constant to avoid getting stuck at 0 or 1
            state.data[1] += state.data[0] >> 32;
            state.data[0] &= 0xFFFFFFFF;
        }
    }

    BlumBlumShub64::BlumBlumShub64(uint64_t seed): state(0, 0, 0, 0){
        reseed(seed);
    }

    uint64_t BlumBlumShub64::generate() {
        uint64_t num = 0;
        for(int i = 0; i < 8; i++){
            propagate();
            num = (num << 8) | (state.data[0] & 0xFF); // Extracting LSB and appending
        }
        return num;
    }

    void BlumBlumShub64::reseed(uint64_t seed) {
        for(int i = 2; i < 4; i++)
            state.data[i] = 0;
        state.data[1] = seed >> 32;
        state.data[0] = seed & 0xFFFFFFFF;
    }

}