/***MERSENNE TWISTER PRNG***/
/*generates 64 bit integers*/
/*Parameters involved
(w,n,m,r)=(64,312,156,31)
*/


#pragma once
#include <iostream>
#include <cstdlib>


#define N_PARAMETER_64 312
#define M_PARAMETER_64 156

#define A_VECTOR_64 0xB5026F5AA96619E9
#define TMPR_MASK_1_64 0xD66B5EF5B4DA0000
#define TMPR_MASK_2_64 0xFDED6BE000000000
#define TMPR_SHIFT_U_64 29
#define TMPR_SHIFT_S_64 17
#define TMPR_SHIFT_T_64 37
#define TMPR_SHIFT_L_64 41
#define UPPERMASK_64 0xFFFFFFFF80000000ULL
#define LOWERMASK_64 0x7FFFFFFFULL

#define N_PARAMETER_32 624
#define M_PARAMETER_32 397

#define A_VECTOR_32 2573724191
#define TMPR_MASK_1_32 0x9d2c5680
#define TMPR_MASK_2_32 0xefc60000
#define TMPR_SHIFT_U_32 11
#define TMPR_SHIFT_S_32 7
#define TMPR_SHIFT_T_32 15
#define TMPR_SHIFT_L_32 18
#define UPPERMASK_32 0x80000000
#define LOWERMASK_32 0x7ffffffff




template <typename T>
class MT
{
    // Main Parameters

    int N; // length of state value vector
    int M; // optimum value as mid
    T A; // vector in the matrix A
    T upperbits; // for obtaining first w-r bits of the number
    T lowerbits;

    // Tempering Parameters:

    T tempering_mask_B;
    T tempering_mask_C;
    T tempering_shift_U;
    T tempering_shift_S;
    T tempering_shift_T;
    T tempering_shift_L;

    //

    T mt[N_PARAMETER_32]; // State Vector

    int mti = N + 1; // Used as index for the array MT.

    T seed; // Seed given from main
    
    // Generate first N pseudo-random numbers as a seed for the algorithm.
    void sgenrand(T);
    void trytransform();
    T temper(T);

    void init32();
    void init64();


public:
    MT(T seed);
    T getran();
            
};


// Generates initial vector.
template <typename T>
void MT<T>::sgenrand(T iniseed)
{
    mt[0] = iniseed & 0x7FFFFFFFULL;
    for (int mti = 1; mti < N; mti++)
    {
        mt[mti] = (mt[mti - 1] * 69069) & 0x7FFFFFFFULL;
    }
}


// If mti>=N, MT algorithm is run to regenerate values.
template <typename T>
void MT<T>::trytransform(){
    if (mti >= N){
        
        T mtrx[2] = {0, A};
        T y; // A temperory variable.
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
template <typename T>
T MT<T>::temper(T y){
    //performing tempering
    y ^= (y >> tempering_shift_U);
    y ^= (y << tempering_shift_S) & tempering_mask_B;
    y ^= (y << tempering_shift_T) & tempering_mask_C;
    y ^= (y >> tempering_shift_L);
    return y;
}

// Main program to get random number.
template <typename T>
T MT<T>::getran()
{

    T y;
    trytransform();
    
    y = temper(mt[mti]);
    mti++;


    return y;
}


/*
template <typename T>
MT<T>::MT(T seed) : seed(seed)
{
    exit(-1);
}
*/

// Constructor for 32-bit random number.
template <>
MT<uint32_t>::MT(uint32_t seed) : seed(seed)
{
    init32();
    sgenrand(seed);
}


// Constructor for 64-bit random number.
template <>
MT<uint64_t>::MT(uint64_t seed) : seed(seed)
{
    init64();
    sgenrand(seed);
}




// Initial values for 32-bit generator.
template <typename T>
void MT<T>::init64(){
    N = N_PARAMETER_64;
    M = M_PARAMETER_64;
    A = A_VECTOR_64;
    upperbits = UPPERMASK_64;
    lowerbits = LOWERMASK_64;
    tempering_mask_B = TMPR_MASK_1_64;
    tempering_mask_C = TMPR_MASK_2_64;
    tempering_shift_U = TMPR_SHIFT_U_64;
    tempering_shift_S = TMPR_SHIFT_S_64;
    tempering_shift_T = TMPR_SHIFT_T_64;
    tempering_shift_L = TMPR_SHIFT_L_64;
}


// Initial values for 64-bit generator.
template <typename T>
void MT<T>::init32(){
    N = N_PARAMETER_32;
    M = M_PARAMETER_32;
    A = A_VECTOR_32;
    upperbits = UPPERMASK_32;
    lowerbits = (int32_t)LOWERMASK_32;
    tempering_mask_B = TMPR_MASK_1_32;
    tempering_mask_C = TMPR_MASK_2_32;
    tempering_shift_U = TMPR_SHIFT_U_32;
    tempering_shift_S = TMPR_SHIFT_S_32;
    tempering_shift_T = TMPR_SHIFT_T_32;
    tempering_shift_L = TMPR_SHIFT_L_32;
}





