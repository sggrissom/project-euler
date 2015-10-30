
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define internal static
#define global static
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t
#define uint32 uint32_t
#define uint64 uint64_t
#define real32 float
#define real64 double

#define b32 bool32
#define s32 int32
#define s64 int64
#define u32 uint32
#define u64 uint64
#define r32 real32
#define r64 real64

#if DEBUG
#define assert(expression) if(!(expression)) {*(int *)0 = 0;}
#else
#define assert(expression)
#endif

#ifndef WIN32
#define LONG "%lld"
#else
#define LONG "%I64d"
#endif

#include "solutions\bignum.c"

s32 main(int32 argc, char *argv[])
{
    int32 x = 5, y = 1;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    } else if (argc == 3) {
        x = atoi(argv[1]);
        y = atoi(argv[2]);
    }

    init();
    
    bigint num;

    createBigint(&num, 1);
    bignumFactorial(&num, x);
    printBigint(&num);

    printf( LONG "\n", sumBigDigits(&num));

    return 0;
}
