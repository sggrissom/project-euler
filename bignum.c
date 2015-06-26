
#define maxDigits 19
#define intDigits 50
#define ZEROLONG "%019I64u"
#define lowMax 9999999999999999999

typedef struct {
    int32 size;
    uint64 *parts;
} bigint;

internal void putInPart(bigint *big, uint64 num, int32 idx)
{
    assert(idx < big->size && idx >= 0);
    *(big->parts + idx) = num;
}

internal uint64 getPart(bigint *big, int32 idx)
{
    assert(idx < big->size && idx >= 0);
    return *(big->parts + idx);
}

internal int64 getInt(char* s, int32 digits)
{
    char* buffer = malloc(sizeof(char) * (digits + 1));
    char* temp = buffer;
    bool32 began = 0;
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

    int64 result = strtoull(buffer, 0, 10);

    free(buffer);
    
    return result;
}

internal void createBigintFromString(bigint* big, char* string)
{
    int32 digits = intDigits - 2*maxDigits;
    putInPart(big, getInt(string, digits), 2);
    putInPart(big, getInt(string + digits, maxDigits), 1);
    putInPart(big, getInt(string + digits + maxDigits, maxDigits), 0);
}

internal void createBigint(bigint *big, uint64 num)
{
    big->size = 1;
    big->parts = malloc(sizeof(uint64) * big->size);
    putInPart(big, num, 0);
}

internal void expandBigint(bigint *big)
{
    ++(big->size);
    uint64 *temp = realloc(big->parts, sizeof(uint64) * big->size);
    if(temp)
    {
        big->parts = temp;
    } else {
        assert(!"realloc failure");
    }
    putInPart(big, 0, big->size - 1);
}

internal void deleteBigint(bigint *big)
{
    free(big->parts);
}

internal void printBigint(bigint *big)
{
    printf("bigint: " LONG, getPart(big, (big->size) - 1 ));

    for(int32 i = big->size - 2;
        i >= 0;
        --i)
    {
        printf(ZEROLONG, getPart(big, i));
    }

    printf("\n");
}

internal void addWithOverflow(bigint *result, uint64 x, uint64 y)
{
    assert (result->size == 2);

    uint64 low, high = 0;
    uint64 uintmaxDiff = UINT64_MAX - x;

    if( uintmaxDiff < y)
    {
        static const uint64 maxDiff = UINT64_MAX - lowMax;
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

    putInPart(result, low, 0);
    putInPart(result, high, 1);
}

global bigint globalPartResult;
internal void init()
{
    globalPartResult.size = 2;
    globalPartResult.parts = malloc(sizeof(uint64) * 2);
}

internal void addTo(bigint *x, bigint *y)
{
    bigint *bigger, *smaller;
    if(x->size < y->size)
    {
        bigger = y;
        smaller = x;
    } else {
        bigger = x;
        smaller = y;
    }
    
    int32 part = 0;
    int32 smallerSize = smaller->size;
    
    while (part < smallerSize)
    {
        addWithOverflow(&globalPartResult, getPart(bigger, part), getPart(smaller, part));
        putInPart(bigger,
                  getPart(&globalPartResult,0),
                  part++);


        if(getPart(&globalPartResult, 1))
        {
            if (part == bigger->size)
            {
                expandBigint(bigger);
            }

            putInPart(bigger,
                      getPart(&globalPartResult, 1) + getPart(bigger, part),
                      part);
        }
    }

    x = bigger;
}