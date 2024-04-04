#include "diceforge.h"
#include <iostream>
#include <fstream>

#define NUM_POINTS 40
#define NOISE_AMP 0.5

int main(int argc, char const *argv[])
{
    DiceForge::XORShift32 rng = DiceForge::XORShift32(time(NULL));

    using real_t = double;
    
    DiceForge::Gaussian noise_gen = DiceForge::Gaussian(1);
    DiceForge::Exponential expnen = DiceForge::Exponential(rng.next_in_crange(0.1, 10), 0);

    std::cout << "original: x0 = " << expnen.get_x0() << ", k = " << expnen.get_k() << std::endl;

    std::vector<double> x;
    std::vector<double> y;

    std::ofstream out = std::ofstream("noisy_data.dat");
    for (int i = 0; i < NUM_POINTS; i++)
    {
        double x1 = rng.next_in_crange(0, 8);
        double y1 = expnen.pdf(x1) * (1 + NOISE_AMP * expnen.get_k() * noise_gen.next(rng.next_unit(), rng.next_unit()));
        x.push_back(x1);
        y.push_back(y1);
        out << x1 << " " << y1 << std::endl;
    }
    out.close();

    DiceForge::Exponential fit = DiceForge::fitToExponential(x, y, 100000, 1e-6);

    std::cout << "fit: x0 = " << fit.get_x0() << ", k = " << fit.get_k() << std::endl;

    FILE* gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "f(x)= x==%f ? 0 : exp(-%f * (x - %f))\n", fit.get_x0(), fit.get_k(), fit.get_x0());
    fprintf(gnuplot, "set samples 1000\n plot 'noisy_data.dat' title 'samples', f(x) title 'fit curve'\n");
    fclose(gnuplot);

    return 0;
}