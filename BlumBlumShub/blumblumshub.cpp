#include <iostream>
#include <numeric>
#include <cmath>

#define data unsigned long long

class BlumBlumShub{
    private:
        data x, p, q, n;

        int find_bitlen(data i){
            // To find no of bits required to represent `i`
            return std::ceil(std::log2(i));
        }

        int generate_bit_lsb(){
            x = (x*x) % n;  // Step propagation
            return x % 2;
        }

        int find_parity(data num) {
            int count = 0;

            // Counting set bits
            while (num) {
                count += num & 1;  // Add 1 if the least significant bit is set
                num >>= 1;        // Right shift to check the next bit
            }

            // Parity is even if the count is even
            return (count % 2 == 0) ? 0 : 1;  // 0 for even parity, 1 for odd parity
        }

        int generate_bit_parity(){
            x = (x*x) % n;
            return find_parity(x);
        }


    public:
        BlumBlumShub(data p, data q, data seed): p(p), q(q), n(p*q), x(seed){
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
                number = (number << 1) | generate_bit_lsb();
            }

            // Tailoring the number to fit range
            number = number % range + min;
            return number;
        }
};

int main(){
    int ITERATIONS = 10;

    // Choose two large prime numbers congruent to 3 (mod 4)
    data p = 7451, q = 8231;
    // Choose a seed value
    data seed = 123456;

    // Creating the PRNG object
    // BlumBlumShub blum(11, 19, 3);
    BlumBlumShub blum(p, q, seed);

    
    // Test loop
    for(int i =0; i < ITERATIONS; i++){
        std::cout << blum.generate_random_number(1, 10) << std::endl;
    }
}