#include"../include/diceforge.h"
#include <cstring>
using namespace std;
using namespace DiceForge;

int seed = 23345;
//long int seed = 937212576;

template <typename T>
int run(bool binary){
    T rng(seed);
    unsigned int num;
    for(int i = 0; i >= 0; i++){
        num=rng.next();
        if (binary==0) cout<<num<<" ";
        else cout.write(reinterpret_cast<const char *>(&num), sizeof(num));
    }
    
    return 0;
}



int main(int num, const char *arg[]){
    
    int mode=-1;
    bool binary=1;
    if (num==3) if (!strcmp(arg[2],"-i")) binary=0; else return 1; 
    
    if (num==2 || num==3){
    	if (!strcmp(arg[1],"bbs")) run<BlumBlumShub32>(binary);
    	if (!strcmp(arg[1],"mt")) run<MT32>(binary);
    	if (!strcmp(arg[1],"nr")) run<NaorReingold>(binary);
    	if (!strcmp(arg[1],"xors")) run<XORShift32>(binary);
    	if (!strcmp(arg[1],"lfsr")) run<LFSR32>(binary);
    
    }
    else return 1;
    
    
    return 0;
}
