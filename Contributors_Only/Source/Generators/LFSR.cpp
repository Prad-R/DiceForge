#include "LFSR.h"
#include <chrono>

unsigned long long int DiceForge::LFSR::generate() {
    unsigned long long int rand_num = 0, new_bit;

    for (int i = 0; i < 64; i++) {
        new_bit = (curr_seed2 ^ (curr_seed2 >> 1) ^ (curr_seed2 >> 2) ^ (curr_seed2 >> 7)) & 1;
        curr_seed2 = (curr_seed2 >> 1) | (curr_seed1 << 63);
        curr_seed1 = (curr_seed1 >> 1) | (new_bit << 63);
        rand_num = rand_num * 2 + (curr_seed2 & 1);
    }
    if (rand_num == ULONG_LONG_MAX){
        return generate();
    }
    else {
        return rand_num;
    }
}

void DiceForge::LFSR::reseed(unsigned long long int seed) {
    if (seed == 0){
        curr_seed1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        curr_seed2 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        generate();
        generate();
    }
    else {
        curr_seed1 = seed;
        curr_seed2 = seed;
    }
}