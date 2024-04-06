# DiceForge

## Overview
This is a simple C++ library for *Pseudo Random Number Generation*. It provides a functionality similar to that of the python standard library *random*. 

## Features

- **Ease of Use**: Straightforward API for quick integration into your C++ projects.
- **Versatility**: Supports different PRNG algorithms, allowing you to choose based on your requirements.
- **Convenience**: Provides various standard distributions used in scientific computation and also has rudimentary support for custom probability distributions. 

### Upcoming Features
- To be decided

## Available PRNGs and Distributions

**Pseudorandom Number Generators**
1. Mersenne Twister (MT)
2. Linear Feedback Shift Register (LFSR)
3. XOR-Shift (XOR)
4. Blum Blum Shub (BBS)
5. Naor-Reingold (NR)

**Distrbutions**

1. Cauchy
2. Exponential
3. Gaussian
4. Maxwell
5. Weibull
6. Bernoulli
7. Binomial
8. Gibbs
9. Hypergeometric
10. Negative-Hypergeometric
11. Poisson

## Benchmarks

### Performance

Time taken for generating *100000000* random numbers by DiceForge's PRNGs:

| Generator | Time Taken |
| --------- | ---------- |
| MT32 | 1780.44 ms |
| MT64 | 1779.17 ms |
| XORShift32 | 445.931 ms |
| XORShift64 | 476.061 ms |
| LFSR32 | 10777.7 ms |
| LFSR64 | 19091.7 ms |
| BBS32 | 50130.6 ms |
| BBS64 | 97033.5 ms |
| NaorReingold | 210082 ms  |

For comparison, benchmarking other existing standard libraries for the same test.

| Generator | Time Taken |
| --------- | ---------- |
| C++'s Mersenne Twister | 4032.7 ms |
| C rand() function| 1388.03 ms |
| python's random | 175175.89 ms (~ 3min) |
| numpy's randint | 165600.48 ms (~ 3min) |

### Dieharder Tests

The various PRNGs in DiceForge are robust and pass various Dieharder tests:

| Generator | Tests Passed | Tests Failed |
| --------- | ------------ | ------------ |
| MT32 | 29 (4 weak) | 1 |
| MT64 | 29 (1 weak) | 1 |
| XORShift32 | 29 | 1 |
| XORShift64 | 29 (1 weak) | 1 |
| BBS32 | 29 (2 weak) | 1 |
| BBS64 | 29 (2 weak) | 1 |
| LFSR32 | 29 (2 weak) | 1 |
| LFSR64 | 29 | 1 |
| Naor Reingold | 19 | 11 |

For more information about the Dieharder tests, check out DiceForge's Documentation.

## Documentation

Check out the [Documentation](docs/DiceForge_Documentation.pdf) for detailed information on library usage, supported algorithms, and more!

## Getting Started

### Prerequisites

- C++ compiler (minimum C++17 or later, note that C++20 is required for using 2D probability functions)
- CMake (>=3.28) [If building library]

### Installation

#### Using a prebuilt library
1. Download the compiled binaries from [out](out) folder along with the include files [include](include)
2. If you want compact compilation commands later on, add the path to *include/* to the environment variable PATH
3. Start generating pseudo-random numbers!

#### Building it yourself
1. Clone the repository: `git clone https://github.com/yourusername/diceforge-library-clone.git`
2. Create the build folder by using the CMakeLists.txt
3. Build library using the given CMake configurations (```cmake --build <build-folder>```)
4. Currently DiceForge supports g++, clang, mingw and their variants but does not support msvc

#### After successfully building you can
* Install the library to *usr/local/* (```cmake --install <build-folder>```) 
* Use it without installation by following the steps mentioned in [Using a prebuilt library](#using-a-prebuilt-library)

## Usage

Here's a quick example to get you started:

*example.cpp*
```cpp
#include "diceforge.h"

int main() {
    // Create a PRNG object
    int seed = 123;
    DiceForge::XORShift32 prng = DiceForge::XORShift32(seed);

    // Generate and print a random number using the prng
    std::cout << "Random number: " << prng.next() << std::endl;

    // Generate and print a random number using DiceForge's default prng
    std::cout << "One more random number: " << DiceForge::Random.next() << std::endl;

    return 0;
}
```

Now to compile it with a compiler of your choice (we use g++ in the following example, also it is assumed that g++ has access toand searches usr/local for installed libraries), enter the following command in your terminal

1. If you installed diceforge
```bash
g++ example.cpp -ldiceforge -o example.out
```

2. If you did not install diceforge and you included diceforge to PATH
```bash
g++ example.cpp libdiceforge.a -o example.out
```
where *libdiceforge.a* is the built static library

3. If you did not install diceforge and you did not include diceforge to PATH 
```bash
g++ example.cpp libdiceforge.a -I "<include>" -o example.out
```
where *\<include\>* is the path to the folder corresponding to [include](include) and *libdiceforge.a* is the built static library

Feel free to explore the library and experiment with different algorithms!

## Contributing

Currently, this is an IIT-M Math Club exclusive project and we aren't accepting outside contributions.

### For Project Members
- View the [Tasks folder](Contributors_Only/Tasks) to view the tasks to be done.

- Reference materials are provided in the [Contributors_Only](Contributors_Only) folder.
