#include "MT.h"

namespace DiceForge
{
    
    // Constructor for 32-bit random number.
    MT32::MT32(uint32_t seed) : seed(seed)
    {
        N = 624;
        M = 397;
        A = 2573724191;
        upperbits = 0x80000000;
        lowerbits = (int32_t)0x7ffffffff;
        tempering_mask_B = 0x9d2c5680;
        tempering_mask_C = 0xefc60000;
        tempering_shift_U = 11;
        tempering_shift_S = 7;
        tempering_shift_T = 15;
        tempering_shift_L = 18;
        mt.resize(N);
        reseed(seed);
    }

    // Reset seed
    void MT32::reseed(uint32_t seed)
    {
        sgenrand(seed);
        mti=N+1;
    }

    // Main program to get random number.
    uint32_t MT32::generate()
    {
        trytransform();      
        uint32_t y = temper(mt[mti]);
        mti++;
        return y;
    }

    // Generates initial vector.
    void MT32::sgenrand(uint32_t iniseed)
    {
        mt[0] = iniseed & 0x7FFFFFFFULL;
        for (int mti = 1; mti < N; mti++)
        {
            mt[mti] = (mt[mti - 1] * 69069) & 0x7FFFFFFFULL;
        }
    }

    // If mti>=N, MT algorithm is run to regenerate values.
    void MT32::trytransform(){
        if (mti >= N){
            
            uint32_t mtrx[2] = {0, A};
            uint32_t y; // A temperory variable.
            int k; // An iterative variable

            for (k = 0; k < N - M; k++)
            {
                y = (mt[k] & upperbits) | (mt[k + 1] & lowerbits); // Performing the linear reccurence transformation
                mt[k] = mt[k + M] ^ (y >> 1) ^ (mtrx[y & 1]);
            }
            for (; k < N - 1; k++)
            {
                y = (mt[k] & upperbits) | (mt[k + 1] & lowerbits);
                mt[k] = mt[k + M - N] ^ (y >> 1) ^ (mtrx[y & 1]);
            }

            y = (mt[N - 1] & upperbits) | (mt[0] & lowerbits);
            mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ (mtrx[y & 1]);

            mti = 0;
        }
    }

    // Tempers generated value before returning.
    uint32_t MT32::temper(uint32_t y){
        //performing tempering
        y ^= (y >> tempering_shift_U);
        y ^= (y << tempering_shift_S) & tempering_mask_B;
        y ^= (y << tempering_shift_T) & tempering_mask_C;
        y ^= (y >> tempering_shift_L);
        return y;
    }


    // Constructor for 64-bit random number.
    MT64::MT64(uint64_t seed) : seed(seed)
    {
        N = 312;
        M = 156;
        A = 0xB5026F5AA96619E9;
        upperbits = 0xFFFFFFFF80000000ULL;
        lowerbits = 0x7FFFFFFFULL;
        tempering_mask_B = 0xD66B5EF5B4DA0000;
        tempering_mask_C = 0xFDED6BE000000000;
        tempering_shift_U = 29;
        tempering_shift_S = 17;
        tempering_shift_T = 37;
        tempering_shift_L = 41;
        mt.resize(N);
        reseed(seed);
    }

    // Reset seed
    void MT64::reseed(uint64_t seed)
    {
        sgenrand(seed);
        mti=N+1;
    }

    // Main program to get random number.
    uint64_t MT64::generate()
    {
        trytransform();      
        uint64_t y = temper(mt[mti]);
        mti++;
        return y;
    }

    // Generates initial vector.
    void MT64::sgenrand(uint64_t iniseed)
    {
        mt[0] = iniseed & 0x7FFFFFFFULL;
        for (int mti = 1; mti < N; mti++)
        {
            mt[mti] = (mt[mti - 1] * 69069) & 0x7FFFFFFFULL;
        }
    }

    // If mti>=N, MT algorithm is run to regenerate values.
    void MT64::trytransform(){
        if (mti >= N){
            
            uint64_t mtrx[2] = {0, A};
            uint64_t y; // A temperory variable.
            int k; // An iterative variable

            for (k = 0; k < N - M; k++)
            {
                y = (mt[k] & upperbits) | (mt[k + 1] & lowerbits); // Performing the linear reccurence transformation
                mt[k] = mt[k + M] ^ (y >> 1) ^ (mtrx[y & 1]);
            }
            for (; k < N - 1; k++)
            {
                y = (mt[k] & upperbits) | (mt[k + 1] & lowerbits);
                mt[k] = mt[k + M - N] ^ (y >> 1) ^ (mtrx[y & 1]);
            }

            y = (mt[N - 1] & upperbits) | (mt[0] & lowerbits);
            mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ (mtrx[y & 1]);

            mti = 0;
        }
    }

    // Tempers generated value before returning.
    uint64_t MT64::temper(uint64_t y){
        //performing tempering
        y ^= (y >> tempering_shift_U);
        y ^= (y << tempering_shift_S) & tempering_mask_B;
        y ^= (y << tempering_shift_T) & tempering_mask_C;
        y ^= (y >> tempering_shift_L);
        return y;
    }
}
