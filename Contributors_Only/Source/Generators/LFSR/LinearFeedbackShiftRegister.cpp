#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>

using namespace std;

long long int lfsr_once()
{
    unsigned long long int curr = chrono::high_resolution_clock::now().time_since_epoch().count();
    long long int rand_num = 0;
    bool new_bit;

    new_bit = ((curr ^ (curr >> 7) ^ (curr << 9) ^ (curr >> 13))) & 1;
    // rand_num = (rand_num + (long double)new_bit) / 2;
    rand_num = rand_num * 2 + new_bit;
    curr = (curr >> 1) | (curr << 63);

    for (int i = 1; i < 4; i++)
    {
        new_bit = ((curr ^ (curr >> 7) ^ (curr << 9) ^ (curr >> 13))) & 1;
        // rand_num = (rand_num + (long double)new_bit) / 2;
        rand_num = rand_num * 2 + new_bit;
        curr = (curr >> 1) | (curr << 63);
    }
    return rand_num;
}

int main()
{
    ofstream MyFile("output.txt");
    for (int i = 0; i < 1000000; i++)
    {
        MyFile << lfsr_once() << '\n';
        // printf("%lld\n", lfsr_once());
    }
    MyFile.close();
}