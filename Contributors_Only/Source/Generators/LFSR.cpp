#include "LFSR.h"
#include <chrono>

unsigned long long int DiceForge::LFSR::generate() {
    unsigned long long int rand_num = 0, new_bit;
    
    // For each bit to generate in rand_num,
    for (int i = 0; i < 64; i++) {
        // Calculate (by the series of taps) the new bit to be added to left of curr_seed
        new_bit = (curr_seed2 ^ (curr_seed2 >> 1) ^ (curr_seed2 >> 2) ^ (curr_seed2 >> 7)) & 1;
        // Shift curr_seed (both parts) to the right, and change the leftmost bit to new_bit
        curr_seed2 = (curr_seed2 >> 1) | (curr_seed1 << 63);
        curr_seed1 = (curr_seed1 >> 1) | (new_bit << 63);
        // Take the last bit of curr_seed as the output, and add it to the right of rand_num
        rand_num = rand_num * 2 + (curr_seed2 & 1);
    }
    return rand_num;
}

void DiceForge::LFSR::reseed(unsigned long long int seed) {
    // If seed is zero, RNG will get stuck at zero. So set both parts of curr_seed to current times
    if (seed == 0){
        curr_seed1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        curr_seed2 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    // If non-zero seed given, set both parts of curr_seed to that value
    else {
        curr_seed1 = seed;
        curr_seed2 = seed;
    }
    // Important: First 128 bits generated will simply be curr_seed in reverse
    // Get them out of the way while reseeding
    generate();
    generate();
}