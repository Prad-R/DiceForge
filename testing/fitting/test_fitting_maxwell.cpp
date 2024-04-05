#include "diceforge.h"
#include <iostream>
#include <fstream>

#define NUM_POINTS 20
#define NOISE_AMP 0.5

int main(int argc, char const *argv[])
{
    DiceForge::XORShift32 rng = DiceForge::XORShift32(time(NULL));

    DiceForge::real_t a = rng.next_in_crange(0.5, 50);
    DiceForge::Gaussian noise_gen = DiceForge::Gaussian(1);
    DiceForge::Maxwell maxwell = DiceForge::Maxwell(a);

    std::cout << "original: a = " << maxwell.get_a() << std::endl;

    std::vector<double> x;
    std::vector<double> y;

    std::ofstream out = std::ofstream("noisy_data.dat");
    for (int i = 0; i < NUM_POINTS; i++)
    {
        double x1 = rng.next_in_crange(0, 3*a);
        double y1 = maxwell.pdf(x1) + NOISE_AMP * M_1_PI * noise_gen.next(rng.next_unit(), rng.next_unit()) / maxwell.get_a();
        x.push_back(x1);
        y.push_back(y1);
        out << x1 << " " << y1 << std::endl;
    }
    out.close();

    DiceForge::Maxwell fit = DiceForge::fitToMaxwell(x, y, 10000, 1e-6);
    
    std::cout << "fit: a = " << fit.get_a() << std::endl;

    FILE* gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "plot 'noisy_data.dat' title 'samples', "\
    "%f * x*x * exp(- x*x / (2*%f)) / (%f) title 'fit curve'\n",
    M_2_SQRTPI / M_SQRT2, pow(fit.get_a(), 2), pow(fit.get_a(), 3));
    fclose(gnuplot);

    return 0;
}