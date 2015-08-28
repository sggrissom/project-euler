
#include <stdio.h>
#include <stdlib.h>

#include "../sgg/sgg.h"

#ifndef WIN32
#define LONG "%lld"
#else
#define LONG "%I64u"
#endif

internal u32
sg_atoi(const char *s)
{
    u32 result;

    while(*s)
    {
        result <<= 1;
        result += (result << 2);
        result += (*s++ & 0x0f);
    }

    return result;
}

internal u32
CharValue(char character)
{
    return character - 'a' + 1;
}

internal u32
GetStringValue(const char *str)
{
    u32 sum = 0;
    
    while(*str)
    {
        sum += CharValue(*str++);
    }

    return sum;
}

internal b32
IsStringLower(char *a, char *b)
{
    b32 Result = 0;

    char CharA = *a++;
    char CharB = *b++;

    while(CharA == CharB)
    {
        CharA = *a++;
        CharB = *b++;
    }

    if(CharB && CharB < CharA)
    {
        Result = 1;
    }

    return Result;
}

internal void
SlowSortStrings(char **StringArray, u32 ArraySize)
{
    for(u32 SortedNumber = 0;
        SortedNumber < ArraySize;
        ++SortedNumber)
    {
        char *MinString = *(StringArray + SortedNumber);
        u32 MinStringIndex = SortedNumber;
        for(u32 SearchIndex = SortedNumber + 1;
            SearchIndex < ArraySize;
            ++SearchIndex)
        {
            if(IsStringLower(MinString, *(StringArray + SearchIndex)))
            {
                MinString = *(StringArray + SearchIndex);
                MinStringIndex = SearchIndex;
            }

        }

        char *temp = *(StringArray + SortedNumber);
        *(StringArray + SortedNumber) = MinString;
        *(StringArray + MinStringIndex) = temp;
    }
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

    printf("open\n"); 
    FILE *file = fopen("names.txt", "r");

    char *str = 0;
    char **strings = 0;

    if(file)
    {
        char character = fgetc(file);
    
        while(character != EOF)
        {
            while(character != '\"' && character != ',')
            {
                buffer_push(str, character);
                character = fgetc(file);
            }
            if(str)
            {
                buffer_push(str, '\0');
                buffer_push(strings, str);
                str = 0;
            }
            character = fgetc(file);
        }

        fclose(file);

    }

    SlowSortStrings(strings, buffer_count(strings));
    
    for(u32 StringIndex = 0;
        StringIndex < buffer_count(strings);
        ++StringIndex)
    {
        printf("%s\n", strings[StringIndex]);
    }
    
    return 0;
}
