#include "Poisson.h"
#include <algorithm>
#include "basicfxn.h"

DiceForge::Poisson::Poisson(DiceForge::real_t lambda)
{
    if (l < 0) {
        throw std::invalid_argument("Lambda must not be negative!");
    }
    
    l=lambda;
    sq=sqrt(2);
    lnl=log(l);
    g=l*lnl-lgamma(l+1);
}

DiceForge::real_t DiceForge::Poisson::variance() const{
    return l;
}

DiceForge::real_t DiceForge::Poisson::expectation() const{
    return l;
}

DiceForge::int_t DiceForge::Poisson::minValue() const{
    return 0;
}

DiceForge::int_t DiceForge::Poisson::maxValue() const{
    return std::numeric_limits<int_t>().infinity();
}


DiceForge::real_t DiceForge::Poisson::pmf(DiceForge::int_t x) const{
    return (pow(l,x)*exp(-l)/tgamma(x+1));
}

DiceForge::real_t DiceForge::Poisson::cdf(DiceForge::int_t x) const{
   DiceForge::real_t sum=0,a=exp(-l);
   for (int i=1; i<=x; i++){
    a = a*(l/i);
    sum+=a;
   }
   return (sum);
}


