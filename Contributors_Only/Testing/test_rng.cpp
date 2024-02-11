#include <iostream>
#include <vector>
#include <fstream>
#include "rng_tester.h"

#define SEED    10101097
#define SAMPLES 10000000

#define TEST_BINS 10
#define TEST_MOD 7

int main() {

    // You can choose any RNG here and check its uniformity
    DiceForge::XORShift32 rng = DiceForge::XORShift32(SEED);

    std::vector<size_t> bfreq = test_bin_frequency(rng, SAMPLES, TEST_BINS);
    std::vector<size_t> mfreq = test_mod_frequency(rng, SAMPLES, TEST_MOD);
    std::vector<DiceForge::real_t> stats = test_statistical(rng, SAMPLES);

    std::cout << "mean: " << stats[0] << ", variance: " << stats[1] << ", min: " << stats[2] << ", max: " << stats[3] << std::endl;

    // Save generated data to files
    std::ofstream out1 = std::ofstream("test_bin.dat");
    std::ofstream out2 = std::ofstream("test_mod.dat");
    if (out1.is_open())
    {
        for (int i = 0; i < TEST_BINS; i++)
        {
            out1 << i << "\t" << bfreq[i] << std::endl;
        }
    }
    out1.close();
    if (out2.is_open())
    {
        for (int i = 0; i < TEST_MOD; i++)
        {
            out2 << i << "\t" << mfreq[i] << std::endl;
        }
    }
    out2.close();

    // Plot histogram using GNUPlot
    FILE* gnuplot = popen("gnuplot", "w");
    std::string cmd = 
    "reset;"
    "set terminal jpeg size 1000, 1000;"\
    "set output 'plot_bin.jpg';"\
    "set boxwidth 0.7;"\
    "set style fill solid;"
    "set title 'Histrogram';"\
    "set xlabel 'Bin containing R_n';"\
    "set ylabel 'Frequency';"\
    "set yrange [0:];"
    "plot 'test_bin.dat'"\
    "using 1:2:xtic(1) w boxes title 'Bins i.e., floor(" + std::to_string(TEST_BINS + 1) + "R_n / R_n^{max}))';\n";
    fprintf(gnuplot, "%s", cmd.c_str());

    cmd = 
    "reset;"
    "set terminal jpeg size 1000, 1000;"\
    "set output 'plot_mod.jpg';"\
    "set boxwidth 0.7;"\
    "set style fill solid;"
    "set title 'Histrogram';"\
    "set xlabel 'Redisue';"\
    "set ylabel 'Frequency';"\
    "set yrange [0:];"
    "plot 'test_mod.dat'"\
    "using 1:2:xtic(1) w boxes title 'Residues mod " + std::to_string(TEST_MOD) + "';\n";
    fprintf(gnuplot, "%s", cmd.c_str());
    fclose(gnuplot);

    return 0;
}