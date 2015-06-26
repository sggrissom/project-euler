
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define internal static
#define LONG "%lld"
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t
#define uint64 uint64_t
#define real32 float

int64 getGridPathNum(int32 x, int32 y)
{
    int64 result = 0;
    if(x == 0 && y == 0)
    {
        result = 0;
    } else if(x == 0 || y == 0) {
        result = 1;
    } else if (x ==y) {
        result = 2 * getGridPathNum(x-1, y);
    } else {
        result = getGridPathNum(x-1,y) + getGridPathNum(x, y-1);
    }

    return result;
}

int32 main(int32 argc, char *argv[])
{
    int32 x = 20, y = 20;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    } else if (argc == 3) {
        x = atoi(argv[1]);
        y = atoi(argv[2]);
    }

    printf("answer: " LONG "\n", getGridPathNum(x,y));

    return 0;
}
