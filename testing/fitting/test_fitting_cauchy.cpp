#include "diceforge.h"
#include <iostream>
#include <fstream>

#define NUM_POINTS 20
#define NOISE_AMP 0.05

int main(int argc, char const *argv[])
{
    DiceForge::XORShift32 rng = DiceForge::XORShift32(time(NULL));

    DiceForge::Gaussian noise_gen = DiceForge::Gaussian(1);
    DiceForge::Cauchy cauchy = DiceForge::Cauchy(rng.next_in_crange(20, 50), rng.next_in_crange(0, 10));

    std::cout << "original: x0 = " << cauchy.get_x0() << ", gamma = " << cauchy.get_gamma() << std::endl;

    std::vector<double> x;
    std::vector<double> y;

    std::ofstream out = std::ofstream("noisy_data.dat");
    for (int i = 0; i < NUM_POINTS; i++)
    {
        double x1 = rng.next_in_crange(10, 50);
        double y1 = cauchy.pdf(x1) + NOISE_AMP * M_1_PI * noise_gen.next(rng.next_unit(), rng.next_unit()) / cauchy.get_gamma();
        x.push_back(x1);
        y.push_back(y1);
        out << x1 << " " << y1 << std::endl;
    }
    out.close();

    DiceForge::Cauchy fit = DiceForge::fitToCauchy(x, y, 100000);
    
    std::cout << "fit: x0 = " << fit.get_x0() << ", gamma = " << fit.get_gamma() << std::endl;

    FILE* gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "plot 'noisy_data.dat' title 'samples', %f/(1 + ((x-%f)*%f)**2) title 'fit curve'\n",
    M_1_PI * 1 / fit.get_gamma(), fit.get_x0(), 1 / fit.get_gamma());
    fclose(gnuplot);

    return 0;
}
