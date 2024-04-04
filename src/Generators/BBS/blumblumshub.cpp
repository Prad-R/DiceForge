#include "blumblumshub.h"
#include <numeric>

namespace DiceForge
{
    const BigInt128 BlumBlumShub32::p = BigInt128(4294967107, 4294967295, 0, 0);
    const BigInt128 BlumBlumShub32::q = BigInt128(4294967039, 4294967295, 0, 0);
    const BigInt128 BlumBlumShub32::n = BlumBlumShub32::p.multiply(BlumBlumShub32::q);

    const BigInt128 BlumBlumShub64::p = BigInt128(4294967107, 4294967295, 0, 0);
    const BigInt128 BlumBlumShub64::q = BigInt128(4294967039, 4294967295, 0, 0);
    const BigInt128 BlumBlumShub64::n = BlumBlumShub64::p.multiply(BlumBlumShub64::q);

    inline void BlumBlumShub32::propagate(){
        state.square();
        // Mod operation
        if(state.data[3] >= n.data[3] && state.data[2] >= n.data[2] && state.data[1] >= n.data[1] && state.data[0] >= n.data[0])
            for(int i = 0; i < 4; i++)
                state.data[i] -= n.data[i];

        // Ensure the state is not 0 or 1
        if(state.data[3] == 0 && state.data[2] == 0 && state.data[1] == 0 && (state.data[0] == 0 || state.data[0] == 1)){
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
        // for(int i = 0; i < 4; i++){
        //     state.data[i] = seed & 0xFFFFFFFF;
        //     seed >>= 32;
        // }
        for(int i = 1; i < 4; i++)
            state.data[i] = 0;
        state.data[0] = seed;
    }

    inline void BlumBlumShub64::propagate(){
        state.square();
        if(state.data[3] >= n.data[3] && state.data[2] >= n.data[2] && state.data[1] >= n.data[1] && state.data[0] >= n.data[0])
            for(int i = 0; i < 4; i++)
                state.data[i] -= n.data[i];

        // Ensure the state is not 0 or 1
        if(state.data[3] == 0 && state.data[2] == 0 && state.data[1] == 0 && (state.data[0] == 0 || state.data[0] == 1)){
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
        // for(int i = 0; i < 4; i++){
        //     state.data[i] = seed & 0xFFFFFFFF;
        //     seed >>= 32;
        // }
        for(int i = 2; i < 4; i++)
            state.data[i] = 0;
        state.data[0] = seed & 0xFFFFFFFF;
        state.data[1] = seed >> 32;
    }
}