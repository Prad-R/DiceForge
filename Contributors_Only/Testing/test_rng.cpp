#include <iostream>
#include <vector>
#include <fstream>
#include "rng_tester.h"

#define SEED    101010
#define SAMPLES 5000

int main() {

    // Test uniformity of XORShift RNG
    DiceForge::XORShift32 rng = DiceForge::XORShift32(SEED);
    std::vector<size_t> freq = test_bin_frequency(rng, SAMPLES, 12);

    std::vector<DiceForge::real_t> stats = test_statistical(rng, SAMPLES);

    std::cout << "mean: " << stats[0] << ", variance: " << stats[1] << ", min: " << stats[2] << ", max: " << stats[3] << std::endl;

    // Save generated data to file test.dat
    std::ofstream out = std::ofstream("bin.dat");
    if (out.is_open())
    {
        for (int i = 0; i < 5; i++)
        {
            out << i << "\t" << freq[i] << std::endl;
        }
    }
    out.close();

    // Plot histogram using GNUPlot
    FILE* gnuplot = popen("gnuplot", "w");
    std::string cmd = 
    "reset;"
    "set terminal jpeg size 1000, 1000;"\
    "set output 'plot.jpg';"\
    "set boxwidth 0.7;"\
    "set style fill solid;"
    "set title 'Location Histrogram';"\
    "set xlabel 'Bin containing R_n';"\
    "set ylabel 'Frequency';"\
    "set yrange [0:];"
    "plot 'bin.dat'"\
    "using 1:2:xtic(1) w boxes title 'Bins i.e., floor(12R_n / R_n^{max}))';\n";
    fprintf(gnuplot, "%s", cmd.c_str());
    fclose(gnuplot);

    return 0;
}