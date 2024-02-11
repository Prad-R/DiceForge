#include <iostream>
#include <functional>

double simpson(std::function<double(double)> f, double a, double b)
{
    /*
    f = function we want to integrate
    a = start point on x axis
    b = end point on x axis
    h = step size, taken as a millionth of the diff btw a and b
    n = number of partitions, taken as a million here
    area = numerical area approximation using simpson's 1/3rd rule 
    */
    double h, area, sum1, sum2, sum3, n;
    n = 1000000;
    h = (b - a) / n;
    sum1 = f(a) + f(b);
    sum2 = sum3 = 0;
    for (int i = 1; i < n; i = i + 2)
    {
        sum2 += f(a + i * h);
    }
    for (int i = 2; i <= n; i = i + 2)
    {
        sum3 += f(a + i * h);
    }
    area = h * (sum1 + 4 * sum2 + 2 * sum3) / 3;
    return area;
}

