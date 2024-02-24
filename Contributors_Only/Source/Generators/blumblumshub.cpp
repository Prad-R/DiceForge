#include "blumblumshub.h"

namespace DiceForge
{
    template <typename T>
    BlumBlumShub<T>::BlumBlumShub(T seed) : state(seed) {
        _genlen = sizeof(T) * 8; // Bit length for generation
        check_seed(seed);
    }

    template <typename T>
    BlumBlumShub<T>::~BlumBlumShub() {
    }

    template <typename T>
    inline void BlumBlumShub<T>::propagate(){
        state = (state * state) % n;

        // Ensure the state is not 0 or 1
        if(state == 0 || state == 1){
            state += 4294967387ULL; // A random constant to avoid getting stuck at 0 or 1
        }
    }

    template <typename T>
    void BlumBlumShub<T>::check_seed(T seed) {
        if (std::gcd(seed, n) != 1)
        {
            std::cerr << "Error: Seed is not coprime with `n = p * q`" << std::endl;
            exit(1);
        }
    }

    template <typename T>
    T BlumBlumShub<T>::generate() {
        T num = 0;
        for(int i = 0; i < _genlen; i++){
            propagate();
            num = (num << 1) | (state % 2); // Extracting LSB and appending
        }
        return num;
    }

    template <typename T>
    void BlumBlumShub<T>::reseed(T seed) {
        state = seed;
    }

    template class BlumBlumShub<uint32_t>;
    template class BlumBlumShub<uint64_t>;
}