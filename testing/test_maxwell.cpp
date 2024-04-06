#include "diceforge.h"
#include <fstream>
#include <iostream>

#define N 1e8
#define bins 200

int main(int argc, char const *argv[])
{
    double a = 4; 
    DiceForge::Maxwell m = DiceForge::Maxwell(a);
    DiceForge::XORShift rng = DiceForge::XORShift(123);

    std::vector<int> b = {0};
    b.reserve(bins+1);

    for (size_t i = 0; i < bins; i++)
    {
        b[i] = 0;
    }

    for (size_t i = 0; i < N; i++)
    {
        double n = m.next(rng.next_unit(), rng.next_unit(), rng.next_unit());
        int bin = fmin(bins, floor(n * bins / (6*a)));
        b[bin]++;
    }

    std::ofstream out = std::ofstream("maxwell.dat");
    out.clear();
    for (size_t i = 0; i < bins; i++)
    {
        out << b[i] << std::endl;
    }
    
    out.close();    

    FILE* gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "plot 'maxwell.dat' title 'maxwell-boltzmann with a = %.2f' w l\n", a);
    fclose(gnuplot);

    return 0;
}
