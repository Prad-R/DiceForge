#include<iostream>
#include "xorshift.h"

int main(){
    DiceForge::XORShift32 rng32(527);

    DiceForge::XORShift64 rng64(216);

    std::cout << "Random numbers from 32-bit RNG:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << rng32.next() << std::endl;
    }

    std::cout << "Random numbers from 64-bit RNG:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << rng64.next() << std::endl;
    }
}