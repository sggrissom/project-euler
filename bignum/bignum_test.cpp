/* ========================================================================
   File: bignum_test.cpp
   Date: 2016-02-01
   Creator: Steven Grissom
   ======================================================================== */

#include <slib.h>
#include "bignum.h"

internal b32
BignumTest()
{
    big_integer Number = {}, OtherNumber = {};
    Number = (u64)0;

    Assert(BigIntegerCount(Number) == 1);

    PrintBignum(Number);
    Assert(Number == 0);

    Number += 30;

    PrintBignum(Number);
    Assert(Number == 30);

    OtherNumber = (u64)2;

    Number += OtherNumber;

    Assert(Number == 32);

    Number *= Number;

    printf("Number:");
    PrintBignum(Number);
    printf("OtherNumber:");
    PrintBignum(OtherNumber);
    Assert(Number == (32*32));
    Assert(OtherNumber == 2);

    --OtherNumber;

    PrintBignum(OtherNumber);
    Assert(OtherNumber == 1);

    big_integer PowOf2 = {}, Big2 = {};

    PowOf2 = (u32)1;
    Big2 = (u32)2;

    for(u32 i = 0;
        i < 4;
        ++i)
    {
        PowOf2 *= Big2;
    }

    PrintBignum(PowOf2);
    Assert(PowOf2 == 2*2*2*2);

    return 1;
}

int main()
{
    Assert(BignumTest());
    printf("Tests Pass!\n");
    
    return 1;
}
