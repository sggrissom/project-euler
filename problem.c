
#include <stdio.h>
#include <stdlib.h>

#include <slib.h>
#include "solutions/bignum.c"

internal void
GetNextFibonacci(bigint *f1, bigint *f2)
{
    bigint fTemp;
    CreateBigint(&fTemp, 0);
    CopyBigint(f1, &fTemp);
    AddTo(f1, f2);
    DeleteBigint(f2);
    CopyBigint(&fTemp, f2);
    DeleteBigint(&fTemp);
}

internal u32
GetDigitsInFibNumber(u32 Fn)
{
    bigint num1, num2;
    CreateBigint(&num1, 1);
    CreateBigint(&num2, 1);
    
    for(u32 FibNumber = 3;
        FibNumber < Fn;
        ++FibNumber)
    {
        GetNextFibonacci(&num1, &num2);
    }

    GetNextFibonacci(&num1, &num2);
    PrintBigint(&num1);

    return GetBignumDigits(&num1);
}

s32 main(s32 argc, char *argv[])
{
    char *cx = "5", *cy = "1";
    if (argc == 2)
    {
        cx = argv[1];
    } else if (argc == 3) {
        cx = argv[1];
        cy = argv[2];
    }

    u32 x = sg_atoi(cx);
    u32 y = sg_atoi(cy);

    init();

    printf("%d\n", GetDigitsInFibNumber(x));

    return 0;
}
