#include <bits/stdc++.h>
using namespace std;

const double alpha = 0.05;
const int noofintervals = 10;

double chisquare(long long freq[],long long expected[],long long degfreedom){
    double chi=0.0;
    for (int i = 0; i < noofintervals; i++)
    {
        chi+=(pow(abs(freq[i]-expected[i]),2)/static_cast<double>(expected[i]));
    }
    
    return chi;
}

int main()
{
    long long noofsamples = 1000;
    double samples[noofsamples];
    std::ifstream inputFile("chisqdata.txt");
    for (long long i = 0; i < noofsamples; i++)
    {
        inputFile >> samples[i];
    }

    const double intervalwidth = 0.1;
    long long freq[noofintervals] = {0};
    for (int i = 0; i < noofsamples; i++)
    {
        freq[(long long)(samples[i] / intervalwidth)]++;
    }
    long long expected[noofintervals];
    for (int i = 0; i < noofintervals; ++i) {
        expected[i] = noofsamples / noofintervals;
    }
    double result = chisquare(freq, expected, noofintervals - 1);
    cout<<result;

        return 0;
}