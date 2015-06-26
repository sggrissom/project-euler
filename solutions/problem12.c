
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define internal static
#define LONG "%lld"
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t
#define uint64 uint64_t
#define real32 float

internal int32 getNumOfDivisors(int32 x)
{
    int32 divs = 0;
    int32 sqroot = (int32) sqrt(x);

    for (int32 i = 1;
         i<=sqroot;
         ++i)
    {
        if (x % i == 0) divs += 2;
    }

    if (sqroot * sqroot == x)
    {
        --divs;
    }

    return divs;
}

internal int32 findTriangleNumberWithDivisors(int32 divMin)
{
    int32 triangle = 0;
    int32 count = 0;
    int32 limit = 50000;
    int32 divisors = 0;
    
    while (divisors < divMin && count++ < limit)
    {
        triangle += count;
        divisors = getNumOfDivisors(triangle);
    }

    return triangle;
}

int32 main(int32 argc, char *argv[])
{
    int32 x = 1, y = 1;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    } else if (argc == 3) {
        x = atoi(argv[1]);
        y = atoi(argv[2]);
    }

    int32 triangle = findTriangleNumberWithDivisors(x);

    printf("answer: %d\n", triangle);

    return 0;
}
