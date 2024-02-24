cmake_minimum_required(VERSION 3.0.0)

# Project settings

project(DiceForge VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

# Build structure

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

file(GLOB SOURCE "Contributors_Only/Source/*.cpp" 
"Contributors_Only/Source/Distributions/*.cpp"
"Contributors_Only/Source/Distributions/Continuous/*.cpp"
"Contributors_Only/Source/Distributions/Discrete/*.cpp"
"Contributors_Only/Source/Generators/*.cpp")

# Output library

add_library(DiceForge ${SOURCE})