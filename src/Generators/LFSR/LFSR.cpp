#include "LFSR.h"
#include <chrono>

DiceForge::LFSR64::LFSR64(uint64_t seed)
{
    reseed(seed);
}

uint64_t DiceForge::LFSR64::generate() {
    uint64_t rand_num = 0;
    uint64_t new_bit;

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
    return rand_num * 0x2545F4914F6CDD1DULL;
}

void DiceForge::LFSR64::reseed(uint64_t seed) {
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
    for (int i = 0; i < 100; i++){
        generate();
    }
}

DiceForge::LFSR32::LFSR32(uint32_t seed)
{
    reseed(seed);
}

uint32_t DiceForge::LFSR32::generate() {
    uint32_t rand_num = 0;
    uint64_t new_bit;

    // For each bit to generate in rand_num,
    for (int i = 0; i < 32; i++) {
        // Calculate (by the series of taps) the new bit to be added to left of curr_seed
        new_bit = (curr_seed2 ^ (curr_seed2 >> 1) ^ (curr_seed2 >> 2) ^ (curr_seed2 >> 7)) & 1;
        // Shift curr_seed (both parts) to the right, and change the leftmost bit to new_bit
        curr_seed2 = (curr_seed2 >> 1) | (curr_seed1 << 63);
        curr_seed1 = (curr_seed1 >> 1) | (new_bit << 63);
        // Take the last bit of curr_seed as the output, and add it to the right of rand_num
        rand_num = rand_num * 2 + (curr_seed2 & 1);
    }
    return rand_num * 0x2545F4914F6CDD1DULL;
}

void DiceForge::LFSR32::reseed(uint32_t seed) {
    // If seed is zero, RNG will get stuck at zero. So set both parts of curr_seed to current times
    if (seed == 0){
        curr_seed1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        curr_seed2 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
        // If non-zero seed given, set both parts of curr_seed to that value
    else {
        uint64_t s = seed;
        curr_seed1 = (s << 32) | s;
        curr_seed2 = (s << 32) | s;
    }
    // Important: First 128 bits generated will simply be curr_seed in reverse
    // Get them out of the way while reseeding
    generate();
    generate();
    generate();
    generate();
    for (int i = 0; i < 200; i++){
        generate();
    }
}
