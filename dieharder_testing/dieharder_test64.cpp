#include<iostream>
#include<string>
#include<cstring>
int main(int num, char *arg[]){
    std::string gen;
    
    if (num==2) gen=std::string(arg[1]);
    else return 1;
    
    std::system((std::string("./gen64 ")+std::string(gen)+(" | dieharder -d ")+std::to_string(0)+std::string(" -c ',' -D test_name -D 32 -D 64 -D pvalues -D 256 -D 32768  -g 200 | tee dieharder_results/")+gen+("64.txt")).c_str());
    for(int i=1; i<18; i++) std::system((std::string("./gen64 ")+std::string(gen)+(" | dieharder -d ")+std::to_string(i)+std::string(" -c ',' -D test_name -D 32 -D 64 -D pvalues -D 256 -D 32768  -g 200 | tee -a dieharder_results/")+gen+("64.txt")).c_str());
    for(int i=100; i<104; i++) std::system((std::string("./gen64 ")+std::string(gen)+(" | dieharder -d ")+std::to_string(i)+std::string(" -c ',' -D test_name -D 32 -D 64 -D pvalues -D 256 -D 32768  -g 200 | tee -a dieharder_results/")+gen+("64.txt")).c_str());
    for(int i=201; i<210; i++) std::system((std::string("./gen64 ")+std::string(gen)+(" | dieharder -d ")+std::to_string(i)+std::string(" -c ',' -D test_name -D 32 -D 64 -D pvalues -D 256 -D 32768  -g 200 | tee -a dieharder_results/")+gen+("64.txt")).c_str());

    return 0;
}
