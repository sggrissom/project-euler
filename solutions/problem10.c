
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define internal static
#define LONG "%lld"
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t
#define uint64 uint64_t

uint32_t isPrime(uint64_t x)
{
    uint32_t isPrime = 1;

    if (x <= 3)
    {
        isPrime = x > 1;
    } else {

        if (x % 2 == 0 || x % 3 == 0)
        {
            isPrime = 0;
        } else {
    
            for(uint64_t i=5;
                i*i<=x;
                i+=6)
            {
                if(x%i == 0 || x % (i+2) == 0)
                {
                    isPrime = 0;
                }
            }
        }
    }

    return isPrime;
}

uint64 sumPrimesBelow(uint64 limit)
{
    uint64 primeSum = 0;
    for (uint64 i=0;
         i<limit;
         ++i)
    {
        if(isPrime(i))
        {
            primeSum+=i;
        }
    }

    return primeSum;
}

int32 main(int32 argc, char *argv[])
{
    uint64 x = 10;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    }
    
    printf("answer: " LONG "\n", sumPrimesBelow(x));

    return 0;
}
