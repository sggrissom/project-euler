
#include <stdio.h>
#include <stdlib.h>

#include "slib.h"

#ifndef WIN32
#define LONG "%lld"
#else
#define LONG "%I64u"
#endif

internal u32
Factorial(u32 X)
{
    u32 Result = 1;

    for(u32 i = 2;
        i <= X;
        ++i)
    {
        Result *= i;
    }

    return Result;
}

internal u32
GetNumberOfDigits(u32 Number)
{
    u32 DigitCount = 0;

    while(Number > 0)
    {
        Number /= 10;
        ++DigitCount;
    }

    return DigitCount;
}

internal u32
GetDigit(u32 Number, u32 Digit)
{
    u32 UpperMask = (u32)pow(10, Digit+1);
    u32 LowerMask = (u32)pow(10, Digit);
    return (Number % (UpperMask)) / LowerMask;
}

internal u32
UpdateDigits(u32 FirstDigit, u32 OtherDigits, u32 Size)
{
    u32 UpdatedNumber = OtherDigits;
    u32 DigitCount = Size - 1;

    for(u32 DigitIndex = 0;
        DigitIndex < DigitCount;
        ++DigitIndex)
    {
        u32 Digit = GetDigit(OtherDigits, DigitIndex);
        if(Digit >= FirstDigit)
        {
            UpdatedNumber += (u32)pow(10, DigitIndex);
        }
    }

    UpdatedNumber += FirstDigit * (u32)pow(10, DigitCount);

    return UpdatedNumber;
}

internal u32
GetPermutation(u32 PermutationNumber, u32 Size)
{
    u32 Result = 0;
    u32 PermutationCount = Factorial(Size);
    u32 SplitPoint = PermutationCount / Size;
    if(PermutationNumber < PermutationCount)
    {
        u32 FirstDigit = (PermutationNumber)/(SplitPoint);
        if(Size == 2)
        {
            //Second digit is either 0 or 1, the opposite of the first digit. So XOR.
            u32 SecondDigit = FirstDigit ^ 1;

             //Should result in 10 or 01;
            Result = FirstDigit * 10 + SecondDigit;
        }
        else
        {
            u32 OtherDigits = GetPermutation(PermutationNumber %
                                             (SplitPoint),
                                             Size - 1);
            
            Result = UpdateDigits(FirstDigit, OtherDigits, Size);
        }
    }

    return Result;
}

s32 main(s32 argc, char *argv[])
{
    char *cx = "10", *cy = "999999";
    if (argc == 2)
    {
        cx = argv[1];
    } else if (argc == 3) {
        cx = argv[1];
        cy = argv[2];
    }

    u32 x = sg_atoi(cx);
    u32 y = sg_atoi(cy);

    printf("%010u\n", GetPermutation(y, x));

    return 0;
}
