
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define internal static
#define bool32 int32_t
#define int32 int32_t
#define int64 int64_t

internal int32 numDigits(int32 x)
{
    int32 count = 0;
    while(x > 0)
    {
        ++count;
        x /= 10;
    }

    return count;
}

internal int32 getDigit(int32 x, int32 digit)
{
    x = x % (int32)pow(10,digit);

    x /= (int32)pow(10,digit-1);

    return x;
}

internal bool32 isPalindrome(int32 x)
{
    bool32 isPal = 1;
    int32 digitCount = numDigits(x);

    for(int i=0; i < digitCount/2; ++i)
    {
        if (getDigit(x, i+1) != getDigit(x, digitCount-i))
        {
            isPal = 0;
        }
    }

    return isPal;
}

internal int32 largestPalidromeProduct(int32 digits)
{
    int32 limit = (int32)pow(10,digits);
    int32 lpp = 0;

    for(int i=0;
        i < limit;
        ++i)
    {
        for(int j=0;
            j < limit;
            ++j)
        {
            int32 product = i*j;
            if(isPalindrome(product) && product > lpp)
            {
                lpp = product;
            }
        }
    }

    return lpp;
}

int main(int argc, char *argv[])
{
    int32 x = 1;
    if (argc == 2)
    {
        x = atoi(argv[1]);
    }

    isPalindrome(990009);
    
    printf( "largest palindrome made of %d-digit products: %d\r\n", x, largestPalidromeProduct(x));

    return 0;
}
