cmake_minimum_required(VERSION 3.0.0)

# Project settings

project(DiceForge VERSION 1.0
                  DESCRIPTION "A C++ library with the same functionality as the random library in python."
                  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Project structure

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

include_directories(${PROJECT_SOURCE_DIR}/src/Core)

# Files to be compiled

set(SRC
"src/Generators/BBS/blumblumshub.cpp"
"src/Generators/LFSR/LFSR.cpp"
"src/Generators/MT/MT.cpp"
"src/Generators/Naor-Reingold/naor_reingold.cpp"
"src/Generators/XORShift/XORShift.cpp"
"src/Distributions/Discrete/Bernoulli/Bernoulli.cpp"
"src/Distributions/Discrete/Binomial/Binomial.cpp"
"src/Distributions/Discrete/Gibbs/Gibbs.cpp"
"src/Distributions/Discrete/Hypergeometric/Hypergeometric.cpp"
"src/Distributions/Discrete/Negative-Hypergeometric/NegHypergeometric.cpp"
"src/Distributions/Discrete/Poisson/Poisson.cpp"
"src/Distributions/Continuous/Cauchy/Cauchy.cpp"
"src/Distributions/Continuous/Exponential/Exponential.cpp"
"src/Distributions/Continuous/Gaussian/Gaussian.cpp"
"src/Distributions/Continuous/Maxwell/Maxwell.cpp"
"src/Distributions/Continuous/Weibull/Weibull.cpp")

# Compile to objects

add_library(objlib OBJECT ${SRC})
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

# Build library

add_library(diceforge_s STATIC $<TARGET_OBJECTS:objlib>)
add_library(diceforge SHARED $<TARGET_OBJECTS:objlib>)