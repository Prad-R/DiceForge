#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

class MT
{
    uint32_t N = 624; // length of state value vector

    uint32_t M = 397; // optimum value as mid

    uint32_t A = 2573724191; // vector in the matrix A

    uint32_t upperbits = 0x80000000; // for obtaining first w-r bits of the number

    uint32_t lowerbits = (uint32_t)0x7ffffffff; // for obtaining last r bits of the number

    // tempering parameters:

    uint32_t tempering_mask_B = 0x9d2c5680;

    uint32_t tempering_mask_C = 0xefc60000;

    uint32_t tempering_shift_U = 11;

    uint32_t tempering_shift_S = 7;

    uint32_t tempering_shift_T = 15;

    uint32_t tempering_shift_L = 18;

    unsigned long mt[624]; // state vector

    int mti = N + 1; // used as index for the array

    uint32_t seed; // seed given from main

public:
    MT(uint64_t seed) : seed(seed)
    {
    }
    void sgenrand(uint32_t iniseed)
    {
        mt[0] = iniseed & 0xffffffff;
        for (int mti = 1; mti < N; mti++)
        {
            mt[mti] = (mt[mti - 1] * 69069) & 0xffffffff;
        }
    }

    uint32_t getran()
    {

        uint32_t y;
        uint32_t mtrx[2] = {0, A};

        if (mti >= N)
        {
            int k;

            if (mti == N + 1) // checking if state vector is initialized or not
            {
                sgenrand(seed);
            }
            for (k = 0; k < N - M; k++)
            {
                y = (mt[k] & upperbits) | (mt[k + 1] & lowerbits);//performing the linear reccurence transformation
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
        y = mt[mti++];
        //performing tempering
        y ^= (y >> tempering_shift_U);
        y ^= (y << tempering_shift_S) & tempering_mask_B;
        y ^= (y << tempering_shift_T) & tempering_mask_C;
        y ^= (y >> tempering_shift_L);

        return y;
    }
};

int main()
{
    auto currentTime = chrono::high_resolution_clock::now().time_since_epoch().count();
    uint32_t seed = currentTime;
    MT randnum(seed);
    vector<int>freq(10,0);
    for (int i = 0; i < 10000000; i++)
    {
      freq[ randnum.getran()%10]++;
    }
     std::ofstream outputFile("freq.txt", std::ios::trunc);
    for (int i = 0; i < 10; i++)
    {
        /* code */
        outputFile<<freq[i]<<","<<i<<endl;
    }

}