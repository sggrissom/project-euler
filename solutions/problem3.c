
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t isPrime(uint64_t x)
{
    uint32_t isPrime = 1;

    if (x <= 3)
    {
        isPrime = x > 1;
    }

    if (x % 2 == 0 || x % 3 == 0)
    {
        isPrime = 0;
    }
    
    for(uint64_t i=5;
        i*i<=x;
        i+=6)
    {
        if(x%i == 0 || x % (i+2) == 0)
        {
            isPrime = 0;
        }
    }

    return isPrime;
}

uint64_t lpf(uint64_t x)
{
    uint64_t factor = x;
    uint64_t sqrtX = (uint64_t) sqrt(x);
    if (!isPrime(x))
    {
        uint64_t i = 2;

        while(i <= sqrtX)
        {
            if (isPrime(i))
            {
                while ((x % i)==0)
                {
                    factor = i;
                    x /= i;
                }
            }

            ++i;
        }
    }

    return factor;
}

uint64_t main(int argc, char *argv[])
{
    uint64_t x = 600851475143;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    }
    
    printf("largest prime factor: %d\n\r", lpf(x));

    return 0;
}
