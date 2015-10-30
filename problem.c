
#include <stdio.h>
#include <stdlib.h>

#include "slib.h"

#ifndef WIN32
#define LONG "%lld"
#else
#define LONG "%I64u"
#endif

#define AbundantNumberLimit 28123

internal u32
SumOfDivisors(u32 Number)
{
    u32 Sum = 0;

    for(u32 PotentialDivisor = 1;
        PotentialDivisor <= (u32)(Number/2);
        ++PotentialDivisor)
    {
        if((Number % PotentialDivisor) == 0)
        {
            Sum += PotentialDivisor;
        }
    }

    return Sum;
}

internal b32
IsAbundant(u32 Number)
{
    return (SumOfDivisors(Number) > Number);
}

typedef struct
{
    u32 *List;
    u32 Length;
} abundant_number_list;


internal void
PopulateAbundantNumberList(abundant_number_list *AbundantNumberList)
{
    u32 *List = 0;
    
    for(u32 PotentialAbundantNumber = 1;
        PotentialAbundantNumber < AbundantNumberLimit;
        ++PotentialAbundantNumber)
    {
        if(IsAbundant(PotentialAbundantNumber))
        {
            buffer_push(List, PotentialAbundantNumber);
        }
    }

    AbundantNumberList->List = List;
    AbundantNumberList->Length = buffer_count(List);
}

internal b32
IsSumOfAbundantNumbers(u32 Number)
{
    b32 Result = 0;

    if(!IsAbundant(Number))
    {
        for(u32 i = 1;
            i <= Number;
            ++i)
        {
            if(IsAbundant(Number))
            {
                u32 Leftover = Number % i;
                b32 NoneLeft = 0;
                if(Leftover)
                {
                    NoneLeft = IsSumOfAbundantNumbers(Leftover) == 1;
                }
                else
                {
                    NoneLeft = 1;
                }

                if(NoneLeft)
                {
                    Result = 1;
                    break;
                }
            }
        }
    }
    else
    {
        Result = 1;
    }

    return Result;
}

internal u32
SumOfAllNumbersNotMadeUpOfAbundantNumbers()
{
    u32 Sum = 0;

    for(u32 PossibleNumber = 1;
        PossibleNumber <= AbundantNumberLimit;
        ++PossibleNumber)
    {
        printf("%d\n", PossibleNumber);
        if(!IsSumOfAbundantNumbers(PossibleNumber))
        {
            Sum += PossibleNumber;
        }
    }
    
    return Sum;
}

s32 main(s32 argc, char *argv[])
{
    char *x = "1", *y = "2";
    if (argc == 2)
    {
        x = argv[1];
    } else if (argc == 3) {
        x = argv[1];
        y = argv[2];
    }

    abundant_number_list AbundantNumberList = {0};

    PopulateAbundantNumberList(&AbundantNumberList);

    printf("%d\n", AbundantNumberList.Length);
    for(u32 i = AbundantNumberList.Length - 5;
        i < AbundantNumberList.Length;
        ++i)
    {
        printf("a%d: %d\n", i, AbundantNumberList.List[i]);
    }

    return 0;
}
