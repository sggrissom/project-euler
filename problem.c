
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define internal static
#define global static
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t
#define uint64 uint64_t
#define real32 float

#if DEBUG
#define assert(expression) if(!(expression)) {*(int *)0 = 0;}
#else
#define assert(expression)
#endif

#ifndef WIN32
#define LONG "%lld"
#else
#define LONG "%I64u"
#endif

#include "bignum.c"

internal int32 addDigits(uint64 number)
{
    int32 sum = 0;
    int32 digit;
    
    printf("num: " LONG , number);

    while(number)
    {
        digit = number % 10;
        sum += digit;
        number /= 10;
    }

    printf(", sum: %d\n", sum);

    return sum;
}

internal int32 sumBigintDigits(bigint *big)
{
    int32 sum = 0;
    for(int32 i=0;
        i < big->size;
        ++i)
    {
        sum += addDigits(getPart(big, i));
    }

    return sum;
}

int32 main(int32 argc, char *argv[])
{
    uint64 x = 65, y = 1;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    } else if (argc == 3) {
        x = atoi(argv[1]);
        y = atoi(argv[2]);
    }

    init();

    bigint sum = {0};
    createBigint(&sum, 2);

    for(int32 i=1;
        i < x;
        ++i)
    {
        addTo(&sum, &sum);
    }

    printBigint(&sum);

    // printf("answer: %d", sumBigintDigits(&sum));

    return 0;
}
