#ifndef DF_TYPES_H
#define DF_TYPES_H

#include <ctype.h>

namespace DiceForge
{
    typedef int int32_t;                 // A signed integer (32 bit)
    typedef __int64_t int64_t;           // A signed integer (64 bit)
    typedef unsigned int uint32_t;       // An unsigned integer (32 bit)
    typedef __uint64_t uint64_t;         // An unsigned integer (64 bit)
    typedef __int128_t int128_t;         // A signed integer (128 bit)
    typedef __uint128_t uint128_t;       // An unsigned integer (128 bit)

    typedef uint64_t uint_t;            // An unsigned integer (64 bit)
    typedef int64_t int_t;              // A signed integer (64 bit)
    typedef double real_t;              // A signed floating point real number (64 bit)
}

#endif
