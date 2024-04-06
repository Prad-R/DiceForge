#ifndef DF_BigInt128_H
#define DF_BigInt128_H

#include "types.h"

namespace DiceForge{
    /**
     * @brief A class representing a 128-bit integer.
     * 
     * This class provides functionality for performing arithmetic operations
     * and modulus operation on 128-bit integers.
     */
    class BigInt128 {
        public:
            uint64_t data[4]; /**< Array to store the components of the 128-bit integer. */
            static const uint64_t _2_32 = 1ULL << 32; /**< Constant representing 2^32. */

            /**
             * @brief Constructs a BigInt128 object with given components.
             * 
             * @param d0 The least significant 64 bits of the BigInt128.
             * @param d1 The second least significant 64 bits of the BigInt128.
             * @param d2 The second most significant 64 bits of the BigInt128.
             * @param d3 The most significant 64 bits of the BigInt128.
             */
            BigInt128(uint64_t d0, uint64_t d1, uint64_t d2, uint64_t d3) {
                data[0] = d0;
                data[1] = d1;
                data[2] = d2;
                data[3] = d3;
            }

            /**
             * @brief Computes the square of the BigInt128 number.
             * 
             * This method calculates the square of the BigInt128 number using
             * an algorithm optimized for 128-bit integers.
             */
            void square() {
                uint64_t product[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // pad with leading zeros

                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        product[i + j] += data[i] * data[j];
                        product[i + j + 1] += product[i + j] >> 32;
                    }
                }

                for(int i = 0; i < 4; i++){
                    data[i] = product[i] & 0xFFFFFFFF;
                }
            }

            /**
             * @brief Computes the modulus of the BigInt128 number.
             * 
             * This method computes the modulus of the BigInt128 number with
             * the given modulus using extended precision arithmetic.
             * 
             * @param n The modulus to compute the BigInt128 number modulo.
             */
            void mod(uint64_t n){
                uint64_t p1 = n >> 32, p2 = n % _2_32;
                if(data[3] > 0 || data[2] > 0 || data[1] > p1 || (data[1] == p1 && data[0] > p2)){
                    uint128_t res = 0;
                    for(int i = 3; i >= 0; i--){
                        res = ((res * _2_32) % n + data[i] % n) % n;
                    }
                    data[3] = 0;
                    data[2] = 0;
                    data[1] = res >> 32;
                    data[0] = res & 0xFFFFFFFF;
                }
            }

            /**
             * @brief Prints the BigInt128 number.
             * 
             * This method prints the components of the BigInt128 number, from
             * most significant to least significant.
             */
            void print() const {
                for (int i = 3; i >= 0; --i) {
                    std::cout << data[i] << " ";
                }
            }
    };
}

#endif