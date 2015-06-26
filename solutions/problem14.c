
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

internal int64 getNextCollatz(int64 n)
{
    int64 result;
    
    if (n & 1)
    {
        result = 3 * n + 1;
    } else {
        result = n/2;
    }

    return result;
}

internal int32 getCollatzChainLength(int64 n)
{
    int32 chainLength = 1;

    while(n != 1)
    {
        n = getNextCollatz(n);
        ++chainLength;
    }
    
    return chainLength;
}

int32 getMaxUnderOneMillion()
{
    int32 max = 0, maxIdx = 0;

    for(int32 i=1;
        i<=1000000;
        ++i)
    {
        int32 chainLength = getCollatzChainLength(i);
        if(chainLength > max)
        {
            max = chainLength;
            maxIdx = i;
        }
    }

    return maxIdx;
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

    printf("answer: %d\n", getMaxUnderOneMillion());

    return 0;
}
