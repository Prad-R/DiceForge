#include "diceforge.h"
#include <iostream>
#include <fstream>

#define NUM_POINTS 50
#define NOISE_AMP 0.01

int main(int argc, char const *argv[])
{
    DiceForge::XORShift32 rng = DiceForge::XORShift32(time(NULL));

    DiceForge::Gaussian noise_gen = DiceForge::Gaussian(1);
    DiceForge::Gaussian gaussian = DiceForge::Gaussian(23, 1);

    std::cout << "original: mu = " << gaussian.get_mu() << ", sigma = " << gaussian.get_sigma() << std::endl;

    std::vector<double> x;
    std::vector<double> y;

    std::ofstream out = std::ofstream("noisy_data_gaussian.dat");
    for (int i = 0; i < NUM_POINTS; i++)
    {
        double x1 = rng.next_in_crange(10, 50);
        double y1 = gaussian.pdf(x1) + NOISE_AMP * M_1_PI * noise_gen.next(rng.next_unit(), rng.next_unit()) / gaussian.get_sigma();
        x.push_back(x1);
        y.push_back(y1);
        out << x1 << " " << y1 << std::endl;
    }
    out.close();

    DiceForge::Gaussian fit = DiceForge::fitToGaussian(x, y, 10000, 0.0000001);
    
    std::cout << "fit: mu = " << fit.get_mu() << ", sigma = " << fit.get_sigma() << std::endl;

    FILE* gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "plot 'noisy_data_gaussian.dat' title 'samples', exp(-(x - %f) * (x - %f) / (2 * %f * %f)) / (%f) title 'Gaussian'\n",
    fit.get_mu(), fit.get_mu(), fit.get_sigma(), fit.get_sigma(), sqrt(2 * M_PI) * fit.get_sigma());
    //fprintf(gnuplot, "plot 'noisy_data_gaussian.dat' title 'samples'\n");
    fclose(gnuplot);

    return 0;
}