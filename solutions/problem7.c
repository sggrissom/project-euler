
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

int64_t getPrime(int64_t x)
{
    int64_t prime = 0, primeNum = 0, i = 2;
    while(primeNum < x)
    {
        if(isPrime(i))
        {
            prime = i;
            ++primeNum;
        }

        ++i;
    }

    return prime;
}

uint64_t main(int argc, char *argv[])
{
    uint64_t x = 10001;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    }
    
    printf("answer: %d\n\r", getPrime(x));

    return 0;
}
