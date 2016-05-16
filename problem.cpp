
#include <stdio.h>
#include <stdlib.h>

#include <slib.h>
#include "bignum/bignum.h"

internal void
GetNextFibonacci(big_integer *f1, big_integer *f2)
{
    big_integer fTemp;
    fTemp = *f2;

    *f2 += *f1;
    *f1 = fTemp;
}

internal u32
GetDigitCount(u64 Num)
{
    u32 DigitCount = 0;

    while(Num > 0)
    {
        ++DigitCount;
        Num /= 10;
    }

    return DigitCount;
}

internal u32
GetBignumDigits(big_integer *bi)
{
    s32 PartCount = (s32)BigIntegerCount(*bi);
    
    u32 DigitCount = 19 * (PartCount - 1);

    DigitCount += GetDigitCount(bi->Parts[PartCount - 1]);
    
    return DigitCount;
}

s32 main(s32 argc, char *argv[])
{
    char *cx = "1", *cy = "1";
    if (argc == 2)
    {
        cx = argv[1];
    } else if (argc == 3) {
        cx = argv[1];
        cy = argv[2];
    }

    u32 x = sg_atoi(cx);
    u32 y = sg_atoi(cy);

    u32 Digits = 0;

    big_integer fib1, fib2;
    fib1 = (u64)1;
    fib2 = (u64)1;

    u32 FibIndex = 1;

    while(Digits < 1000)
    {
        GetNextFibonacci(&fib1, &fib2);
        Digits = GetBignumDigits(&fib1);
        printf("%d(%d): \n", ++FibIndex, Digits);
//        PrintBignum(fib1);
    }

    printf("\nfib index: %d\n", FibIndex);

    return 0;
}
