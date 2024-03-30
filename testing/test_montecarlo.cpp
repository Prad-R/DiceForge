#include "diceforge.h"
#include <time.h>
#include <fstream>

int main(int argc, char const *argv[])
{
    DiceForge::XORShift rng = DiceForge::XORShift(time(NULL));
    std::ofstream f_out = std::ofstream("pi_out.dat");
    std::ofstream f_in = std::ofstream("pi_in.dat");

    if (argc < 2)
    {
        std::cout << "Enter number of points to generate!" << std::endl;
        return -1;
    }

    int num_samples = atoi(argv[1]);
    int inside = 0;

    for (int i = 0; i < num_samples; i++)
    {
        double x = rng.next_in_crange(0, 1);
        double y = rng.next_in_crange(0, 1);

        if (x*x + y*y <= 1)
        {
            inside++;

            if (i % 1000 == 0)
                f_in << x << " " << y << std::endl;
        }
        else
        {
            if (i % 1000 == 0)   
                f_out << x << " " << y << std::endl;
        }
    }

    f_out.close();
    f_in.close();
    
    double pi = 4 * double(inside)/num_samples;

    std::cout << "pi = " << pi << std::endl;

    FILE* gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "set label 'π = %f' at 0.3, 0.3\n", pi);
    fprintf(gnuplot, "set label 'samples = %d' at 0.3, 0.35\n", num_samples);
    fprintf(gnuplot, "f(x) = sqrt(1 - x*x)\n");
    fprintf(gnuplot, "set xrange [0:1]\n");    
    fprintf(gnuplot, "plot f(x) title 'unit quarter circle' with l, 'pi_out.dat' title '(showing 1 out of every 1000 points)' pt 6 ps 0.2," \
    "'pi_in.dat' title '' pt 7 ps 0.2\n");
    fclose(gnuplot);
    
    return 0;
}
