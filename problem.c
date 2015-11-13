
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

    for(u3 i = 2;
        i <= X;
        ++i)
    {
        Result *= X;
    }

    return Result;
}

internal u32
GetPermutations(u32 PermutationNumber, u32 Size)
{
    u32 Result = 0;

    u32 *Numbers = (u32 *)malloc(Size * sizeof(u32));

    for(u32 i = 0;
        i < Size;
        ++i)
    {
        Numbers[i] = i;
    }

    u32 PermutationCount = Factorial(Size);
    u32 *Permutations = (u32 *)malloc(Size * sizeof(u32));

    u32 index = 0;

    for(u32 i = 0;
        i < Size;
        ++i)
    {
    }
    
    return Result;
}

s32 main(s32 argc, char *argv[])
{
    char *cx = "5", *cy = "3";
    if (argc == 2)
    {
        cx = argv[1];
    } else if (argc == 3) {
        cx = argv[1];
        cy = argv[2];
    }

    u32 x = sg_atoi(cx);
    u32 y = sg_atoi(cy);

    printf("%d\n", GetLexigraphicPermutation(x, y));

    return 0;
}
