#include "LFSR.h"
#include <chrono>

long long int DiceForge::LFSR::generate(){
    long long int rand_num = 0;
    bool new_bit;

    for (int i = 0; i < 63; i++) {
        new_bit = ((curr_seed ^ (curr_seed >> 7) ^ (curr_seed << 9) ^ (curr_seed >> 13))) & 1;
        if (i != 0) {
            rand_num = rand_num * 2 + new_bit;
        }
        curr_seed = (curr_seed >> 1) | (curr_seed << 63);
    }
    curr_seed = rand_num;
    return rand_num;
}

void DiceForge::LFSR::reseed(long long seed){
    if (seed == 0){
        curr_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    else {
        curr_seed = seed;
    }
}