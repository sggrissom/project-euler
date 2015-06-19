
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define internal static
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t

typedef bool32 (*test) (int32, int32);

internal bool32 isDivisibleByRange(int32 x, int32 limit)
{
    bool32 isEveenlyDivisible = 1;
    for (int32 i = limit;
         i>0;
         --i)
    {
        if(x % i)
        {
            isEveenlyDivisible = 0;
            break;
        }
    }

    return isEveenlyDivisible;
}

internal bool32 testUntilTrue(test f, int32 rangeLimit)
{
    int32 testNumber = 0;
    while(!f(++testNumber, rangeLimit)){}

    return testNumber;
}

int main(int argc, char *argv[])
{
    int32 x = 10;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    }
    
    printf( "smallest even divisor in range 0-%d: %d\r\n", x, testUntilTrue(isDivisibleByRange,x));

    return 0;
}
