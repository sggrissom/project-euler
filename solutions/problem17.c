
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

char *ones[] = {"zero",
                "one",
                "two",
                "three",
                "four",
                "five",
                "six",
                "seven",
                "eight",
                "nine"};

char *teens[] = {"ten",
                 "eleven",
                 "twelve",
                 "thirteen",
                 "fourteen",
                 "fifteen",
                 "sixteen",
                 "seventeen",
                 "eighteen",
                 "nineteen"};

char *tens[] = { "zero",
                 "ten",
                 "twenty",
                 "thirty",
                 "forty",
                 "fifty",
                 "sixty",
                 "seventy",
                 "eighty",
                 "ninety"};

internal int32 getDigit(int32 num, int32 digit)
{
    assert (digit > 0);
    return num % (int32)pow(10, digit + 1) / (int32)pow(10, digit);
}

internal char* numToString(int32 num)
{
    assert(num < 10000);

    int32 size = 1000;
    char* string = malloc(sizeof(char) * size);
    sprintf_s(string, size, "");
    int32 digit[4];

    for(int32 i = 0;
        i < 4;
        ++i)
    {
        digit[i] = getDigit(num, i);
    }

    if (digit[3])
    {
        sprintf_s(string, size, "%s thousand ", ones[digit[3]]);
    }

    if (digit[2])
    {
        sprintf_s(string, size, "%s%s hundred ", string, ones[digit[2]]);

    }
    
    if ((digit[3] || digit[2]) && (digit[1] || digit[0]))
    {
        sprintf_s(string, size, "%sand ", string);
    }

    if (digit[1])
    {
        if(digit[1] == 1)
        {
            sprintf_s(string, size, "%s%s", string, teens[digit[0]]);
        } else {
            sprintf_s(string, size, "%s%s", string, tens[digit[1]]);
            if(digit[0])
            {
                sprintf_s(string, size, "%s-%s", string, ones[digit[0]]);
            }
        }
    } else if (digit[0]) {
        sprintf_s(string, size, "%s%s", string, ones[digit[0]]);
    }

    sprintf_s(string, size, "%s\0", string);

    return string;
}

internal int32 numCharsInString(char* string)
{
    int32 count = 0;

    while(*string)
    {
        char token = *string++;
        if (token >= 'a' && token <= 'z')
        {
            ++count;
        }
    }

    return count;
}

internal int32 lettersInNumber(int32 num)
{
    char* string = numToString(num);

    return numCharsInString(string);
}

internal int32 numLettersUpTo(int32 num)
{
    int32 count = 0;

    for (int32 i=1;
         i <= num;
         ++i)
    {
        count += lettersInNumber(i);
    }

    return count;
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

    

    printf("%d\n", numLettersUpTo(x));

    return 0;
}
