
#include <stdio.h>
#include <stdlib.h>

#include "slib.h"

#ifndef WIN32
#define LONG "%lld"
#else
#define LONG "%I64u"
#endif

typedef struct
{
    u32 *List;
    u32 Length;
} abundant_number_list;

#define AbundantNumberLimit 28123
global abundant_number_list AbundantNumberList;

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

internal void
PopulateAbundantNumberList()
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

    AbundantNumberList.List = List;
    AbundantNumberList.Length = buffer_count(List);
}

internal b32
IsInAbundantList(u32 Number)
{
    b32 Result = 0;
    
    for(u32 i = 0;
        i < AbundantNumberList.Length;
        ++i)
    {
        if(AbundantNumberList.List[i] == Number)
        {
            Result = 1;
            break;
        }
    }

    return Result;
}

internal u32
AbundantListIndexOfLimit(u32 Number)
{
    u32 Result = 0;

    for(u32 i = 0;
        i < AbundantNumberList.Length;
        ++i)
    {
        if(AbundantNumberList.List[i] >= Number)
        {
            Result = i;
            break;
        }
    }

    return Result;
}

internal b32
IsSumOfAbundantNumbers(u32 Number)
{
    u32 Limit = AbundantListIndexOfLimit(Number);

    for(u32 i = 0;
        i < Limit;
        ++i)
    {
        for(u32 j = 0;
            j < Limit;
            ++j)
        {
            u32 Sum = AbundantNumberList.List[i] + AbundantNumberList.List[j];
            if(Sum == Number)
            {
                return 1;
            }
        }
    }

    return 0;
}

internal u32
SumOfAllNumbersNotMadeUpOfAbundantNumbers()
{
    u32 Sum = 0;

    for(u32 PossibleNumber = 1;
        PossibleNumber < AbundantNumberLimit;
        ++PossibleNumber)
    {
        if(!IsSumOfAbundantNumbers(PossibleNumber))
        {
            Sum += PossibleNumber;
            if(PossibleNumber > 22000)
                printf("%d\n", PossibleNumber);
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

    PopulateAbundantNumberList();

    printf("%d\n", SumOfAllNumbersNotMadeUpOfAbundantNumbers());

    return 0;
}
