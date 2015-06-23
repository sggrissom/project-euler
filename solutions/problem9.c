
/*

a + b + c = sum
c = sum - (a+b)

a^ + b^ = c^

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define internal static
#define LONG "%lld"
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t

typedef struct
{
    int32 a;
    int32 b;
    int32 c;
} triplet;

triplet findPythagorean(int32 sum)
{
    triplet t = {};

    for(int a=1;
        a < sum/2;
        ++a)
    {
        for(int b=a;
            b<sum/2;
            ++b)
        {
            int32 c = sum - (a+b);
        
            printf("%d %d %d\n", a,b,c);
            if (pow(a,2) + pow(b,2) == pow(c,2))
            {
                t.a = a;
                t.b = b;
                t.c = c;
            
                return t;
            }
        }
    }

    return t;
}

    int main(int argc, char *argv[])
    {
        int32 x = 12;
        if (argc == 2)
        {
            x = atoi(argv[1]);
        }

        triplet trip = findPythagorean(x);
        
        printf("answer: %d %d %d\n", trip.a, trip.b, trip.c);
        printf("product: %d\n", trip.a * trip.b * trip.c);

        return 0;
    }
