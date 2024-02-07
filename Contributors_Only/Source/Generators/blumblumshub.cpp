#include <iostream>
#include <numeric>
#include <cmath>

// For ease of use, defining `data` to represent unsigned long long
#define data unsigned long long

namespace BitGen{
    enum BitGenType{
        // Enum for types of bit generation
        LSB,
        PARITY
    };

    int get_lsb(data x){
        // Gets least significant bit of `x`
        return x % 2;
    }

    int get_parity_bit(data num) {
        // Gets the parity bit for `x`
        int count = 0;

        // Counting set bits
        while (num) {
            count += num & 1;  // Add 1 if the least significant bit is set
            num >>= 1;        // Right shift to check the next bit
        }

        // Parity is even if the count is even
        return (count % 2 == 0) ? 0 : 1;  // 0 for even parity, 1 for odd parity
    }
}


class BlumBlumShub{
    // A Pseudo-Random Number Generator using the BlumBlumShub algorithm
    private:
        data x, p, q, n;
        int (*get_bit)(data);

        int find_bitlen(data i){
            // Utility function to find no of bits required to represent `i`
            return std::ceil(std::log2(i));
        }

        int generate_bit(){
            // Propagates the seed and returns bit extracted from current seed
            x = (x*x) % n;
            return get_bit(x);
        }


    public:
        BlumBlumShub(
                data p, data q, data seed,
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
                    get_bit = *BitGen::get_lsb;
                    break;

                case BitGen::PARITY:
                    get_bit = *BitGen::get_parity_bit;
                    break;
                
                default:
                    std::cerr << "Error: Invalid bit generator type given" << std::endl;
                    exit(1);
            }
        };

        data generate_random_number(data min, data max){
            // Validating range
            if (min > max) {
                std::cerr << "Error: Invalid range" << std::endl;
                exit(1);
            }

            // finding range, [max, min] both inclusive
            data range = max - min + 1;

            // generating number bit by bit
            // iteration done for no of bits required for given range
            data number = 0;
            for(int i = 0; i < find_bitlen(range); i++){
                number = (number << 1) | generate_bit();
            }

            // Tailoring the number to fit range
            number = number % range + min;
            return number;
        }
};

int main(){
    int ITERATIONS = 10;

    // Choosing two large prime numbers congruent to 3 (mod 4)
    data p = 7451, q = 8231;
    // Choose a seed value
    data seed = 123456;

    // Creating the PRNG object
    // BlumBlumShub blum(11, 19, 3);
    // BlumBlumShub blum(p, q, seed, BitGen::BitGenType::LSB);
    BlumBlumShub blum(p, q, seed, BitGen::BitGenType::PARITY);

    
    // Test loop
    for(int i =0; i < ITERATIONS; i++){
        std::cout << blum.generate_random_number(1, 10) << std::endl;
    }
}