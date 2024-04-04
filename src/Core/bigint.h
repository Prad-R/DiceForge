#ifndef DF_BigInt128_H
#define DF_BigInt128_H

#include "types.h"

namespace DiceForge{

    class BigInt128 {
        public:
            uint64_t data[4];
        
            // Constructor
            BigInt128(uint64_t d0, uint64_t d1, uint64_t d2, uint64_t d3) {
                data[0] = d0;
                data[1] = d1;
                data[2] = d2;
                data[3] = d3;
            }

            // Function to multiply two BigInt128 numbers
            BigInt128 multiply(const BigInt128& num) const {
                uint64_t product[8]; // pad with leading zeros

                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        product[i + j] += data[i] * num.data[j];
                        product[i + j + 1] += product[i + j] >> 32;
                        product[i + j] &= 0xFFFFFFFF;
                    }
                }

                return BigInt128(product[0], product[1], product[2], product[3]);
            }

            void square() {
                uint64_t product[8]; // pad with leading zeros

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
    };
}

#endif