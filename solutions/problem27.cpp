
#include <stdio.h>
#include <stdlib.h>

#include <slib.h>

internal b32
IsPrime(s64 x)
{
    b32 isPrime = true;

    if (x <= 3)
    {
        isPrime = x > 1;
    }
    else
    {
        if (x % 2 == 0 || x % 3 == 0)
        {
            isPrime = false;
        } else {
    
            for(s32 i=5;
                i*i<=x;
                i+=6)
            {
                if(x%i == 0 || x % (i+2) == 0)
                {
                    isPrime = false;
                }
            }
        }
    }

    return isPrime;
}

internal u32
ConsequtivePrimesFromCoefficients(s64 a, s64 b)
{
    u32 Result = 0;
    b32 IsValuePrime = true;
    u64 PrimeIndex = 0;
    
    while(IsValuePrime)
    {
        s64 EquationResult = PrimeIndex * PrimeIndex + a * PrimeIndex + b;
        IsValuePrime = IsPrime(EquationResult);
        if(IsValuePrime)
        {
            ++Result;
        }
        
        ++PrimeIndex;
    }

    return Result;
}

s32 main(s32 argc, char *argv[])
{
    char *cx = "3", *cy = "1";
    if (argc == 2)
    {
        cx = argv[1];
    } else if (argc == 3) {
        cx = argv[1];
        cy = argv[2];
    }

//    u32 x = sg_atoi(cx);
//    u32 y = sg_atoi(cy);

    u32 MaxPrimes = 0;
    s64 BestA = 0, BestB = 0;

    s64 MaxValue = 1000;

    for(s64 AValue = 0;
        AValue < MaxValue;
        ++AValue)
    {
        for(s64 BValue = 0;
            BValue < MaxValue;
            ++BValue)
        {
            u32 Primes = ConsequtivePrimesFromCoefficients(AValue, BValue);
            if(Primes > MaxPrimes)
            {
                MaxPrimes = Primes;
                BestA = AValue;
                BestB = BValue;
            }
            BValue = -BValue;
            Primes = ConsequtivePrimesFromCoefficients(AValue, BValue);
            if(Primes > MaxPrimes)
            {
                MaxPrimes = Primes;
                BestA = AValue;
                BestB = BValue;
            }
            AValue = -AValue;
            Primes = ConsequtivePrimesFromCoefficients(AValue, BValue);
            if(Primes > MaxPrimes)
            {
                MaxPrimes = Primes;
                BestA = AValue;
                BestB = BValue;
            }
            BValue = -BValue;
            Primes = ConsequtivePrimesFromCoefficients(AValue, BValue);
            if(Primes > MaxPrimes)
            {
                MaxPrimes = Primes;
                BestA = AValue;
                BestB = BValue;
            }
            AValue = -AValue;

        }
    }

    printf("%d\n", BestA * BestB);

    return 0;
}
