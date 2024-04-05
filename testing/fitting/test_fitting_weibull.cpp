#include "diceforge.h"
#include <iostream>
#include <fstream>

#define NUM_POINTS 20
#define NOISE_AMP 0.05

int main(int argc, char const *argv[])
{
    DiceForge::XORShift32 rng = DiceForge::XORShift32(time(NULL));

    using real_t = double;
    
    DiceForge::Gaussian noise_gen = DiceForge::Gaussian(1);
    DiceForge::Weibull bull = DiceForge::Weibull(rng.next_in_range(1, 10), rng.next_in_crange(0.1, 10));

    std::cout << "original: lambda = " << bull.get_lambda() << ", k = " << bull.get_k() << std::endl;

    std::vector<double> x;
    std::vector<double> y;

    std::ofstream out = std::ofstream("noisy_data.dat");
    for (int i = 0; i < NUM_POINTS; i++)
    {
        double x1 = rng.next_in_crange(0, 10);
        double y1 = bull.pdf(x1) + NOISE_AMP * M_1_PI * noise_gen.next(rng.next_unit(), rng.next_unit()) / bull.get_lambda();
        x.push_back(x1);
        y.push_back(y1);
        out << x1 << " " << y1 << std::endl;
    }
    out.close();

    DiceForge::Weibull fit = DiceForge::fitToWeibull(x, y, 100000, 1e-6);

    std::cout << "fit: lambda = " << fit.get_lambda() << ", k = " << fit.get_k() << std::endl;

    FILE* gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "plot 'noisy_data.dat' title 'samples', %f/%f * ((x/%f) ** (%f - 1)) * exp(-((x/%f)**%f)) title 'fit curve'\n",
    fit.get_k(), fit.get_lambda(), fit.get_lambda(), fit.get_k(), fit.get_lambda(), fit.get_k());
    fclose(gnuplot);

    return 0;
}