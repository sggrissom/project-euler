
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define internal static
#define global static
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t
#define uint64 uint64_t
#define real32 float

#if DEBUG
#define assert(expression) if(!(expression)) {*(int *)0 = 0;}
#else
#define assert(expression)
#endif

#ifndef WIN32
#define LONG "%lld"
#else
#define LONG "%I64u"
#endif

char *number_triangle = "75 "
    "95 64 "
    "17 47 82 "
    "18 35 87 10 "
    "20 04 82 47 65 "
    "19 01 23 75 03 34 "
    "88 02 77 73 07 63 67 "
    "99 65 04 28 06 16 70 92 "
    "41 41 26 56 83 40 80 70 33 "
    "41 48 72 33 47 32 37 16 94 29 "
    "53 71 44 65 25 43 91 52 97 51 14 "
    "70 11 33 28 77 73 17 78 39 68 17 57 "
    "91 71 52 38 17 14 91 43 58 50 27 29 48 "
    "63 66 04 68 89 53 67 30 73 16 69 87 40 31 "
    "04 62 98 27 23 09 70 98 73 93 38 53 60 04 23 ";

int32 *numTriangle;

internal void createNumberTriangle()
{
    numTriangle = malloc(sizeof(int32) * 15 * 15);
    int32 *ptr = numTriangle;
    char *scanner = number_triangle;

    while(*scanner)
    {
        *ptr++ = atoi(scanner);
        while(*scanner++ != ' ') {}
    }
}

internal int32 getNumAtCoordinate(int32 row, int32 offset)
{
    for (int32 i=1;
         i <= row;
         ++i)
    {
        offset += i; 
    }
    
    return *(numTriangle + offset);
}

internal int32 getMaxTrianglePathSum(int32 x, int32 y)
{
    if (x == 14) return getNumAtCoordinate(x, y);
    int32 leftSum = getMaxTrianglePathSum(x + 1, y);
    int32 rightSum = getMaxTrianglePathSum(x + 1, y + 1);
    int32 max = leftSum > rightSum ? leftSum : rightSum;

    return max + getNumAtCoordinate(x,y);
}

internal int32 getLargestPathSum()
{
    return getMaxTrianglePathSum(0,0);
}

int32 main(int32 argc, char *argv[])
{
    int32 x = 5, y = 1;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    } else if (argc == 3) {
        x = atoi(argv[1]);
        y = atoi(argv[2]);
    }

    createNumberTriangle();

    printf("%d\n", getLargestPathSum());

    return 0;
}
