
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

internal bool32 getDay(int32 year, int32 month, int32 date)
{
    
}

internal bool32 isDateValid(int32 year, int32 month, int32 date, bool32 isLeapYear)
{
    bool32 result = 0;
    
    if (month > 0 && month <= 12)
    {
        if (date <= 31) {
            if(date > 0 && date <= 28)
            {
                result = 1;
            } else {
                if (month == 4 ||
                    month == 6 ||
                    month == 9 ||
                    month == 11)
                {
                    if(date <= 30)
                    {
                        result = 1;
                    }
                } else if (month == 2)
                {
                    if(date < 29 || (isLeapYear && date == 29))
                    {
                        result = 1;
                    }
                } else {
                    result = 1;
                }
            }
        }
    }

    return result;
}

internal int32 sundayCount()
{
    int32 count = 0;
    int32 year = 1900, month = 1, date = 1, day = 1, isLeapYear = 0;

    while (year < 2001)
    {
        while(isDateValid(year, month, date, isLeapYear))
        {
            while(isDateValid(year, month, date, isLeapYear))
            {
                ++date;
                ++day;
                if (day == 8) day = 1;
            }

            ++month;
            date = 1;

            if(year > 1900 && year < 2001 && day == 7)
            {
                ++count;
            }
        }

        ++year;
        month = 1;
        date = 1;

        
        if (((year % 4) == 0) &&
            ((year % 100) > 0 || (year % 400) == 0))
        {
            isLeapYear = 1;
        } else {
            isLeapYear = 0;
        }
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

    printf("%d\n", sundayCount());

    return 0;
}
