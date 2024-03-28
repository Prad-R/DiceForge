# DiceForge

## Overview
This is a simple C++ library for *Pseudo Random Number Generation (PRNG)*. It provides a functionality similar to that of the python std library *random*. 

## Features

- **Ease of Use**: Straightforward API for quick integration into your C++ projects.
- **Versatility**: Supports different PRNG algorithms, allowing you to choose based on your requirements.
- **Seed Control**: Easily set and manipulate the seed for reproducibility.

### Upcoming Features
- Applying distributions to uniform random generators to make biased generators
- Detailed documentation on distrbutions

## Supported PRNG Algorithms

1. Mersenne Twister (MT)
2. Linear Congruential Generator (LCG)
3. XOR-Shift (XOR)
4. Blum Blum Shub (B.B.S.)
5. Naor-Reingold (NR)

## Supported Distrbutions

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

### Statistical Analysis

| Generator | mean | variance |
| --------- | ---- | -------- |
| BBS32  | 0.500189 | 0.0834384 |
| BBS64  | 0.499066 | 0.0834061 |
| XOR32  | 0.499978 | 0.08334 |
| XOR64  | 0.499931 | 0.0833327 |
| MT32   | 0.499956 | 0.0833425 |
| MT64   | 0.500034 | 0.0833241 |
| LFSR32 | 0.500033 | 0.0833329 |
| LFSR64 | 0.49994, | 0.0833352 |
| NR     | 0.341687 | 0.0498607 |

### Time Performance
Generating *100000000* random numbers:

#### DiceForge:
| Generator | Time Taken |
| --------- | ---------- |
| XorShift32 | 435.497ms |
| XorShift64 | 410.498ms |
| BBS32 | 14780ms |
| BBS64 | 24568.6ms |
| MT32 | 1738.91ms |
| MT64 | 1811.27ms |
| LFSR | 18540.7ms |
| Naor Reingold | 7143ms|

For comparison, benchmarking other existing standard libraries for the same test.

| Generator | Time Taken |
| --------- | ---------- |
| C++ MT| 4032.7ms |
| C++ rand()| 1388.03ms |
| python randint | 51171.51641845703  ms |
| numpy randint | 194015.43641090393 ms |


## Documentation
Check out the [Documentation](https://www.overleaf.com/project/65d9eea60dbb4690fe6ff8be) for detailed information on library usage, supported algorithms, and more!

## Getting Started

### Prerequisites

- C++ compiler (supporting C++11 or later)
- CMake (>=3.28) [If building library]

### Installation

#### Using a  prebuilt library
1. Download the library file from [out](out) folder and add to PATH
2. Make sure the [include](include) folder is PATH
3. Start generating pseudo-random numbers!

#### Building it yourself
1. Clone the repository: `git clone https://github.com/yourusername/prng-library.git`
2. Create the build folder by using the CMakeLists.txt
2. Build library using the given CMake configurations (```cmake --build <build-folder>```)
3. After the build is sucessful, follow the steps mentioned in [Using a prebuilt library](#using-a-prebuilt-library)

## Usage

Here's a quick example to get you started:

```cpp
#include "diceforge.h"

int main() {
    // Create a PRNG object
    DiceForge::XORShift32 prng = DiceForge::XORShift32(123);

    // Generate and print a random number
    std::cout << "Random Number: " << prng.next() << std::endl;

    return 0;
}
```

Feel free to explore the library and experiment with different algorithms!

## Contributing

Currently, this is an IIT-M Maths CLub exclusive project and we aren't accepting outside contributions.

### For Project Members
- View the [Tasks folder](Contributors_Only/Tasks) to view the tasks to be done.

- Reference materials are provided in the [Contributers_Only](Contributors_Only) folder.

Current TODO
- [ ] Custom pdf
- [ ] Exception handling
- [ ] 2d rv
- [ ] Documentation
- [ ] Testing the RNGs