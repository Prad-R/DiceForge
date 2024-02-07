#pragma once
#include <iostream>
#include <numeric>
#include <cmath>
#include <type_traits>

namespace BitGen{
    enum BitGenType{
        // Enum for types of bit generation
        LSB,
        PARITY
    };

    template <typename T>
    int find_bitlen(T i){
        // Utility function to find no of bits required to represent `i`
        return std::ceil(std::log2(i));
    }

    template <typename T>
    int get_lsb(T x){
        // Gets least significant bit of `x`
        return x % 2;
    }

    template <typename T>
    int get_parity_bit(T num) {
        // Gets the parity bit for `x`
        int count = 0;

        // Counting set bits
        while (num > 0) {
            count += num & 1;  // Add 1 if the least significant bit is set
            num >>= 1;        // Right shift to check the next bit
        }

        // Parity is even if the count is even
        return (count % 2 == 0) ? 0 : 1;  // 0 for even parity, 1 for odd parity
    }
}

namespace DiceForge
{   
    template <typename T>
    class BlumBlumShub{
        // A Pseudo-Random Number Generator using the BlumBlumShub algorithm
        private:
            T x, p, q, n;
            int (*get_bit)(T);

            inline void next(){
                // Propagates the seed
                x = (x*x) % n;
            }

            int generate_bit(){
                next();
                // returns bit extracted from current seed
                return get_bit(x);
            }


        public:
            BlumBlumShub(
                    T p, T q, T seed,
                    BitGen::BitGenType type = BitGen::LSB): p(p), q(q), n(p*q), x(seed){
                // Validating that p and q are both congruent to 3 (mod 4)
                if ((p % 4 != 3) || (q % 4 != 3)) {
                    std::cerr << "Error: p and q must be congruent to 3 (mod 4)" << std::endl;
                    exit(1);
                }

                // Validating that p and q are co-prime
                if (std::gcd(p, q) != 1) {
                    std::cerr << "Error: p and q must be co-prime" << std::endl;
                    exit(1);
                }

                // Performing check on seed
                // Co-prime check
                if(std::gcd(x, n) != 1) {
                    std::cerr << "Error: Seed is not coprime with `n = p * q`" << std::endl;
                    exit(1);
                }
                // Check for specific unviable seeds
                if(x == 1) {
                    std::cerr << "Error: Seed cannot be 1" << std::endl;
                    exit(1);
                }
                if(x == 0) {
                    std::cerr << "Error: Seed cannot be 0" << std::endl;
                    exit(1);
                }

                // Validating and assigning the bit generation method according to choice
                switch (type) {
                    case BitGen::LSB:
                        get_bit = *BitGen::get_lsb<T>;
                        break;

                    case BitGen::PARITY:
                        get_bit = *BitGen::get_parity_bit<T>;
                        break;
                    
                    default:
                        std::cerr << "Error: Invalid bit generator type given" << std::endl;
                        exit(1);
                }
            };

            template <typename I>
            I generate_random_number(I min, I max){
                // Validating range
                if (min > max) {
                    std::cerr << "Error: Invalid range" << std::endl;
                    exit(1);
                }

                // finding range, [max, min] both inclusive
                I range = max - min + 1;

                // generating number bit by bit
                // iteration done for no of bits required for given range
                I number = 0;
                for(int i = 0; i < BitGen::find_bitlen(range); i++){
                    number = (number << 1) | generate_bit();
                }

                // Tailoring the number to fit range
                number = number % range + min;
                return number;
            }
    };
}