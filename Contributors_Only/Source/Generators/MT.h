/***MERSENNE TWISTER PRNG***/
/*generates 64 bit integers*/
/*Parameters involved
(w,n,m,r)=(64,312,156,31)
*/

#ifndef DF_MT_H
#define DF_MT_H

#pragma once
#include <cstdlib>
#include "generator.h"
#include <vector>


namespace DiceForge{

    template <typename T>
    class MT:public Generator<T>
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

        std::vector<T> mt; // State Vector

        int mti = N + 1; // Used as index for the array MT.

        T seed; // Seed given from main
        
        // Generate first N pseudo-random numbers as a seed for the algorithm.
        void sgenrand(T);
        void trytransform();
        T temper(T);

        void init32();
        void init64();
        T generate() override;
        void reseed(T seed) override;

    public:
        MT(T seed);
                
    };

    typedef MT<uint32_t> MT32;
    typedef MT<uint64_t> MT64;

}

#endif