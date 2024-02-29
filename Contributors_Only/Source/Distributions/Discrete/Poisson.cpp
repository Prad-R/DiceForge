#include "Poisson.h"
#include <algorithm>
#include "../../basicfxn.h"



//DiceForge::int_t n;
template <typename T>
DiceForge::Poisson<T>::Poisson(DiceForge::real_t lambda, int32_t s): generator(s)
{
    // Display error if n is not at least 1
    
    
    if (l < 0) {
        std::cerr << "Error :"
                     "\n\tDiceForge::Poisson::Poisson(real_t x_arr[], real_t func_arr[], int len, real_t beta) : "
                     "\n\t\tLambda must not be negative.\n" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    
    
    l=lambda;
    sq=sqrt(2);
    lnl=log(l);
    g=l*lnl-lgamma(l+1);

}

template <typename T>
DiceForge::real_t DiceForge::Poisson<T>::getran(){

    return (0);
}


template <typename T>
DiceForge::int_t DiceForge::Poisson<T>::next(){


    real_t t,x,c;
    do{
        do{
            t=tan(M_PI*generator.next_unit());
            x=sq*t+l;
        } while (x<0);
        x=floor(x);
        c=0.9*(1+t*t)*exp(x*lnl-lgamma(x+1)-g);
    } while(generator.next_unit()>c);


    return int_t(x);
}

template <typename T>
DiceForge::real_t DiceForge::Poisson<T>::variance() const{
    return l;
}

template <typename T>
DiceForge::real_t DiceForge::Poisson<T>::expectation() const{
    return l;
}

template <typename T>
DiceForge::int_t DiceForge::Poisson<T>::minValue() const{
    return 0;
}

template <typename T>
DiceForge::int_t DiceForge::Poisson<T>::maxValue() const{
    return INT64_MAX;
}

template <typename T>
DiceForge::real_t DiceForge::Poisson<T>::pmf(DiceForge::int_t x) const{
    return (pow(l,x)*exp(-l)/tgamma(x+1));
}

template <typename T>
DiceForge::real_t DiceForge::Poisson<T>::cdf(DiceForge::int_t x) const{
   DiceForge::real_t sum=0,a=exp(-l);
   for (int i=1; i<=x; i++){
    a = a*(l/i);
    sum+=a;
   }
   return (sum);
}


