#include "LFSR.h"
#include <chrono>

unsigned long long int DiceForge::LFSR::generate() {
    reseed(0);
    unsigned long long int rand_num = 0;
    bool new_bit;

    for (int i = 0; i < 64; i++) {
        //new_bit = ((curr_seed ^ (curr_seed >> 1) ^ (curr_seed >> 2) ^ (curr_seed >> 7))) & 1;
        new_bit = ((curr_seed ^ (curr_seed << 13) ^ (curr_seed >> 7) ^ (curr_seed << 17))) & 1;
        rand_num = rand_num * 2 + new_bit;
        curr_seed = (curr_seed >> 1) | (curr_seed << 63);
    }
    if (rand_num == LONG_LONG_MAX){
        return generate();
    }
    else {
        return rand_num;
    }
}

void DiceForge::LFSR::reseed(unsigned long long int seed) {
    if (seed == 0){
        curr_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    else {
        curr_seed = seed;
    }
}