#include "Gibbs.h"
#include <algorithm>


void DiceForge::Gibbs::specify(real_t x_arr[], real_t func_arr[], int len, real_t beta){
    n = len;
    free(cumulative);
    free(prob);
    free(x_array);

    std::pair<double,double> xy_arr[n];
    for (int i = 0; i < n; i++){
        xy_arr[i].first = x_arr[i];
        xy_arr[i].second = func_arr[i];
    }
    std::sort(xy_arr, xy_arr + n);

    for (int i = 1; i < n; i++) {
        if (xy_arr[i].first == xy_arr[i - 1].first) {
            std::cerr << "Error :"
                         "\n\tDiceForge::Gibbs::specify(real_t x_arr[], real_t func_arr[], int len, real_t beta) : "
                         "\n\t\tAll x values in x_arr must be unique.\n" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    x_array = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++){
        x_array[i] = xy_arr[i].first;
    }
    auto *prefixSum = (real_t *)malloc(n * sizeof(real_t));
    auto *probabilities = (real_t *)malloc(n * sizeof(real_t));
    real_t prev = 0;
    for (int i = 0; i < n; i++){
        probabilities[i] = exp(- beta * xy_arr[i].second);
        prefixSum[i] = prev + probabilities[i];
        prev = prefixSum[i];
    }
    cumulative = prefixSum;
    prob = probabilities;
}


double DiceForge::Gibbs::next(real_t r){
    return x_array[(std::upper_bound(cumulative, cumulative + n, r * cumulative[n - 1]) - cumulative)];
}


double DiceForge::Gibbs::variance(){
    double exp = expectation();
    double s = 0;
    for (int i = 0; i < n; i++){
        s += prob[i] * (x_array[i] - exp) * (x_array[i] - exp);
    }
    return s;
}


double DiceForge::Gibbs::expectation(){
    double s = 0;
    for (int i = 0; i < n; i++){
        s += prob[i] * x_array[i];
    }
    return s;
}


double DiceForge::Gibbs::minValue(){
    double minV = std::numeric_limits<double>::max();
    for (int i = 0; i < n; i++){
        if (x_array[i] < minV){
            minV = x_array[i];
        }
    }
    return minV;
}


double DiceForge::Gibbs::maxValue(){
    double maxV = std::numeric_limits<double>::min();
    for (int i = 0; i < n; i++){
        if (x_array[i] > maxV){
            maxV = x_array[i];
        }
    }
    return maxV;
}


double DiceForge::Gibbs::pmf(double x){
    double *ptr = std::upper_bound(x_array, x_array + n, x);
    if (ptr == x_array + n or *ptr != x){
        return 0;
    }
    return prob[ptr - x_array];
}


double DiceForge::Gibbs::cdf(double x){
    double *ptr = std::upper_bound(x_array, x_array + n, x);
    if (ptr == x_array){
        return 0;
    }
    return cumulative[ptr - x_array - 1];
}