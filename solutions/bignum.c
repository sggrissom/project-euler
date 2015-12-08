
/*
  Use:

  bigint num;
  CreateBigint(&num, 1);

  Do Something...
  
  PrintBigint(&num);
  
 */

#define maxDigits 19
#define intDigits 50
#define ZEROLONG "%019I64u"
#define lowMax 9999999999999999999

typedef struct {
    u32 size;
    u64 *parts;
} bigint;

internal void
PutInPart(bigint *big, u64 num, s32 idx)
{
    Assert((u32)idx < big->size && idx >= 0);
    *(big->parts + idx) = num;
}

internal u64
GetPart(bigint *big, s32 idx)
{
    Assert((u32)idx < big->size && idx >= 0);
    return *(big->parts + idx);
}

internal s64
GetInt(char* s, s32 digits)
{
    char* buffer = malloc(sizeof(char) * (digits + 1));
    char* temp = buffer;
    b32 began = 0;
    for (int i = 0;
         i<digits;
         ++i)
    {
        if(*s)
        {
            if(began)
            {
                *temp++ = *s++;
            } else if (*s != '0') {
                began = 1;
                *temp++ = *s++;
            } else {
                ++s;
            }
        } else {
            break;
        }
    }
    *temp = '\0';

    s64 result = strtoull(buffer, 0, 10);

    free(buffer);
    
    return result;
}

internal void
CreateBigintFromString(bigint* big, char* string)
{
    s32 digits = intDigits - 2*maxDigits;
    PutInPart(big, GetInt(string, digits), 2);
    PutInPart(big, GetInt(string + digits, maxDigits), 1);
    PutInPart(big, GetInt(string + digits + maxDigits, maxDigits), 0);
}

internal void
CreateBigint(bigint *big, u64 num)
{
    big->size = 1;
    big->parts = malloc(sizeof(u64) * big->size);
    PutInPart(big, num, 0);
}

internal void
ExpandBigint(bigint *big)
{
    ++(big->size);
    u64 *temp = realloc(big->parts, sizeof(u64) * big->size);
    if(temp)
    {
        big->parts = temp;
    } else {
        Assert(!"realloc failure");
    }
    PutInPart(big, 0, big->size - 1);
}

internal void
DeleteBigint(bigint *big)
{
    free(big->parts);
}

internal void
CopyBigint(bigint *original, bigint *copy)
{
    for(u32 idx = 0;
        idx < original->size;
        ++idx)
    {
        ExpandBigint(copy);
        PutInPart(copy, GetPart(original, idx), idx);
    }
}

internal void
PrintBigint(bigint *big)
{
    printf("bigint: " LONG, GetPart(big, (big->size) - 1 ));

    for(s32 i = big->size - 2;
        i >= 0;
        --i)
    {
        printf(ZEROLONG, GetPart(big, i));
    }

    printf("\n");
}

internal void
AddWithOverflow(bigint *result, u64 x, u64 y)
{
    u64 low, high = 0;
    u64 uintmaxDiff = UINT64_MAX - x;

    if( uintmaxDiff < y)
    {
        static const u64 maxDiff = UINT64_MAX - lowMax;
        low = x + y + maxDiff;
        high = 1;
    } else {
        low = x + y;
    }

    if(low > lowMax)
    {
        high = 1;
        low -= lowMax + 1;
    }

    PutInPart(result, low, 0);
    PutInPart(result, high, 1);
}

global bigint globalPartResult;
internal void
init()
{
    globalPartResult.size = 2;
    globalPartResult.parts = malloc(sizeof(u64) * 2);
}

internal void
AddTo(bigint *bigger, bigint *smaller)
{
    s32 part = 0;
    s32 smallerSize = smaller->size;

    s64 nextSmallerPart = GetPart(smaller, part);
    
    while (part < smallerSize)
    {
        AddWithOverflow(&globalPartResult, GetPart(bigger, part), nextSmallerPart);
        PutInPart(bigger,
                  GetPart(&globalPartResult,0),
                  part++);


        nextSmallerPart = GetPart(smaller, part);

        u32 partLevel = part;
        while(GetPart(&globalPartResult, 1))
        {
            if (partLevel == bigger->size)
            {
                ExpandBigint(bigger);

                PutInPart(bigger,
                          GetPart(&globalPartResult,1),
                          partLevel++);

                PutInPart(&globalPartResult, 0, 1);

            } else {
                AddWithOverflow(&globalPartResult,
                                GetPart(&globalPartResult, 1),
                                GetPart(bigger, partLevel));

                PutInPart(bigger,
                          GetPart(&globalPartResult,0),
                          partLevel++);

            }
        }
    }
}

internal void
mult(bigint *big, u32 num)
{
    bigint *multBig = malloc(sizeof(bigint));

    multBig->size = 0;
    multBig->parts = 0;

    CopyBigint(big, multBig);
        
    for(u32 idx = 0;
        idx < num-1;
        ++idx)
    {
        AddTo(big, multBig);
    }
}

internal u64
SumDigits(u64 num)
{
    u64 sum = 0;

    while(num)
    {
        sum += num % 10;
        num = num/10;
    }

    return sum;
}

internal u32
GetNumberOfDigits(u64 Number)
{
    u32 DigitCount = 0;

    while(Number > 0)
    {
        Number /= 10;
        ++DigitCount;
    }

    return DigitCount;
}

internal u64
SumBigDigits(bigint *num)
{
    u64 sum = 0;

    for(u32 idx = 0;
        idx < num->size;
        ++idx)
    {
        sum += SumDigits(GetPart(num, idx));
    }

    return sum;
}

internal void
BignumFactorial(bigint *big, u32 factorialNumber)
{
    for(u32 idx = 1;
        idx < factorialNumber + 1;
        ++idx)
    {
        mult(big,idx);
    }
}

internal u32
GetBignumDigits(bigint *big)
{
    u32 digits = 0;
    
    for(u32 idx = 0;
        idx < big->size;
        ++idx)
    {
        digits += GetNumberOfDigits(GetPart(big, idx));
    }

    return digits;
}
