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

        int generate_bit(){
            x = (x*x) % n;  // Step propagation
            return x % 2;
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
                number = (number << 1) | generate_bit();
            }

            // Tailoring the number to fit range
            number = number % range + min;
            return number;
        }
};
