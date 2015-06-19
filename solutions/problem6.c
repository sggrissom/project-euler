
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define internal static
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t

internal int64 sumSq_sqSum_diff(int64 rangeEnd)
{
    int64 sumsq = 0, sqsum = 0, sum = 0;
    for(int64 i=1;
        i<=rangeEnd;
        ++i)
    {
        sqsum += (int64)pow(i,2);
        sum+=i;
    }

    sumsq = (int64)pow(sum,2);

    int64 difference = sumsq - sqsum;

    difference = difference < 0 ? -difference : difference;

    return difference;
}

int main(int argc, char *argv[])
{
    int64 x = 10;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    }
    
    printf( "answer: %d\r\n", sumSq_sqSum_diff(x));

    return 0;
}
