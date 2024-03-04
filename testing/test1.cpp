#include <iostream>
#include <fstream>
#include <random>

#include "diceforge.h"
#include "rng_tester.h"

void test_all_time(const size_t N);
void test_all_stats(const size_t N);

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        std::cerr << "Enter number of random numbers to be tested :(" << std::endl;
        return -1;
    }

    int N = atoi(argv[1]);

    std::cout << "Generating " << N << " random numbers :)\n\n";
    if (argc >= 3)
    {
        std::string type = std::string(argv[2]);
        if (type == "s" || type == "S")
            test_all_stats(N);        
        else if (type == "t" || type == "T")
            test_all_time(N);
        else
        {
            test_all_stats(N);
            test_all_time(N);
        }
    }
    else
    {
        test_all_stats(N);
        test_all_time(N);
    }

    return 0;
}

void test_all_time(const size_t N)
{
    DiceForge::BlumBlumShub32 bb1 = DiceForge::BlumBlumShub32(123);
    DiceForge::BlumBlumShub64 bb2 = DiceForge::BlumBlumShub64(123);
    DiceForge::XORShift32 xs1 = DiceForge::XORShift32(123);
    DiceForge::XORShift64 xs2 = DiceForge::XORShift64(123);
    DiceForge::MT32 mt1 = DiceForge::MT32(123);
    DiceForge::MT64 mt2 = DiceForge::MT64(123);
    DiceForge::LFSR32 lfsr1 = DiceForge::LFSR32(123);
    DiceForge::LFSR64 lfsr2 = DiceForge::LFSR64(123);
    DiceForge::NaorReingold32 nr = DiceForge::NaorReingold32(123);

    std::cout << "Time performance" << std::endl;

    std::cout << "BBS32\tfloats: " << test_time_floats(bb1, N) << "ms, ints: " << test_time_integers(bb1, N) << "ms" <<  std::endl;

    std::cout << "BBS64\tfloats: " << test_time_floats(bb2, N) << "ms, ints: " << test_time_integers(bb2, N) << "ms" <<  std::endl;

    std::cout << "XOR32\tfloats: " << test_time_floats(xs1, N) << "ms, ints: " << test_time_integers(xs1, N) << "ms" <<  std::endl;

    std::cout << "XOR64\tfloats: " << test_time_floats(xs2, N) << "ms, ints: " << test_time_integers(xs2, N) << "ms" <<  std::endl;

    std::cout << "MT32\tfloats: " << test_time_floats(mt1, N) << "ms, ints: " << test_time_integers(mt1, N) << "ms" <<  std::endl;

    std::cout << "MT64\tfloats: " << test_time_floats(mt2, N) << "ms, ints: " << test_time_integers(mt2, N)  << "ms" <<  std::endl;

    std::cout << "LFSR32\tfloats: " << test_time_floats(lfsr1, N) << "ms, ints: " << test_time_integers(lfsr1, N) << "ms" <<  std::endl;

    std::cout << "LFSR64\tfloats: " << test_time_floats(lfsr2, N) << "ms, ints: " << test_time_integers(lfsr2, N)  << "ms" <<  std::endl;

    std::cout << "NR\tfloats: " << test_time_floats(nr, N) << "ms, ints: " << test_time_integers(nr, N)  << "ms" <<  std::endl;

    std::random_device rd{};    
    std::mt19937 engine{rd()};
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    std::chrono::time_point start_c1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i++)
    {
        dist(engine);
    }
    std::chrono::time_point end_c1 = std::chrono::high_resolution_clock::now();

    std::cout << "C++ MT: " << (end_c1 - start_c1).count() * 1.e-6 << "ms" <<  std::endl;
}

void test_all_stats(const size_t N)
{
    DiceForge::BlumBlumShub32 bb1 = DiceForge::BlumBlumShub32(123);
    DiceForge::BlumBlumShub64 bb2 = DiceForge::BlumBlumShub64(123);
    DiceForge::XORShift32 xs1 = DiceForge::XORShift32(123);
    DiceForge::XORShift64 xs2 = DiceForge::XORShift64(123);
    DiceForge::MT32 mt1 = DiceForge::MT32(123);
    DiceForge::MT64 mt2 = DiceForge::MT64(123);
    DiceForge::LFSR32 lfsr1 = DiceForge::LFSR32(123);
    DiceForge::LFSR64 lfsr2 = DiceForge::LFSR64(123);
    DiceForge::NaorReingold32 nr = DiceForge::NaorReingold32(123);

    std::cout << "Statistical performance" << std::endl;

    auto stats = test_statistical(bb1, N);
    std::cout << "BBS32\tmean: " << stats[0] << ", variance: " << stats[1] <<  std::endl;

    stats = test_statistical(bb2, N);
    std::cout << "BBS64\tmean: " << stats[0] << ", variance: " << stats[1] <<  std::endl;

    stats = test_statistical(xs1, N);
    std::cout << "XOR32\tmean: " << stats[0] << ", variance: " << stats[1] <<  std::endl;

    stats = test_statistical(xs2, N);
    std::cout << "XOR64\tmean: " << stats[0] << ", variance: " << stats[1] <<  std::endl;

    stats = test_statistical(mt1, N);
    std::cout << "MT32\tmean: " << stats[0] << ", variance: " << stats[1] <<  std::endl;

    stats = test_statistical(mt2, N);
    std::cout << "MT64\tmean: " << stats[0] << ", variance: " << stats[1] <<  std::endl;

    stats = test_statistical(lfsr1, N);
    std::cout << "LFSR32\tmean: " << stats[0] << ", variance: " << stats[1] <<  std::endl;

    stats = test_statistical(lfsr2, N);
    std::cout << "LFSR64\tmean: " << stats[0] << ", variance: " << stats[1] <<  std::endl;

    stats = test_statistical(nr, N);
    std::cout << "NR\tmean: " << stats[0] << ", variance: " << stats[1] <<  std::endl;

    std::cout << "\n\n";
}