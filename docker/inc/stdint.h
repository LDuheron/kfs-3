#ifndef STDINT_H
#   define STDINT_H

// DEFINING INTEGER TYPES
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

// DEFINING LIMITS
// Char limits 
#define INT8_MIN (-((int_8t)1 << (8 * sizeof(int_8t) - 1)))
#define INT8_MAX ((int_8t)((1 << (8 * sizeof(int_8t) - 1)) - 1))

#define UINT8_MAX ((uint_8t)((1 << (8 * sizeof(uint_8t))) - 1))

// Short limits 
#define INT16_MIN (-((int_16t)1 << (8 * sizeof(int_16t) - 1)))
#define INT16_MAX ((int_16t)((1 << (8 * sizeof(int_16t) - 1)) - 1))

#define UINT16_MAX ((uint16_t)((1 << (8 * sizeof(uint16_t))) - 1))

// Int limits
#define INT32_MIN (-((int32_t)1 << (8 * sizeof(int32_t) - 1)))
#define INT32_MAX ((int32_t)((1 << (8 * sizeof(int32_t) - 1)) - 1))

#define UINT32_MAX ((uint32_t)((1 << (8 * sizeof(uint32_t))) - 1))

// Long limits
#define INT64_MIN (-((int64_t)1 << (8 * sizeof(int64_t) - 1)))
#define INT64_MAX ((int64_t)((1 << (8 * sizeof(int64_t) - 1)) - 1))

#define UINT64_MAX ((uint64_t)((1 << (8 * sizeof(uint64_t))) - 1))

typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

typedef int8_t intmin_t;
typedef uint8_t uintmin_t;

#endif
