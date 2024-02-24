#include "Gibbs.h"
#include <algorithm>


void DiceForge::Gibbs::specify(int_t x_arr[], real_t func_arr[], int len, real_t beta){
    n = len;
    free(cumulative);
    free(prob);
    free(x_array);

    std::pair<int,double> xy_arr[n];
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

    x_array = (int *)malloc(n * sizeof(int));
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
    for (int i = 0; i < n; i++){
        probabilities[i] /= prefixSum[n - 1];
        prefixSum[i] /= prefixSum[n - 1];
    }
    cumulative = prefixSum;
    prob = probabilities;
}


int DiceForge::Gibbs::next(real_t r){
    return x_array[(std::upper_bound(cumulative, cumulative + n, r) - cumulative)];
}


double DiceForge::Gibbs::variance() const{
    double exp = expectation();
    double s = 0;
    for (int i = 0; i < n; i++){
        s += prob[i] * (x_array[i] - exp) * (x_array[i] - exp);
    }
    return s;
}


double DiceForge::Gibbs::expectation() const{
    double s = 0;
    for (int i = 0; i < n; i++){
        s += prob[i] * x_array[i];
    }
    return s;
}


int DiceForge::Gibbs::minValue() const{
    int minV = std::numeric_limits<int>::max();
    for (int i = 0; i < n; i++){
        if (x_array[i] < minV){
            minV = x_array[i];
        }
    }
    return minV;
}


int DiceForge::Gibbs::maxValue() const{
    int maxV = std::numeric_limits<int>::min();
    for (int i = 0; i < n; i++){
        if (x_array[i] > maxV){
            maxV = x_array[i];
        }
    }
    return maxV;
}


double DiceForge::Gibbs::pmf(int x) const{
    int *ptr = std::upper_bound(x_array, x_array + n, x);
    if (ptr == x_array or *(ptr-1) != x){
        return 0;
    }
    return prob[ptr - x_array - 1];
}


double DiceForge::Gibbs::cdf(int x) const{
    int *ptr = std::upper_bound(x_array, x_array + n, x);
    if (ptr == x_array){
        return 0;
    }
    return cumulative[ptr - x_array - 1];
}