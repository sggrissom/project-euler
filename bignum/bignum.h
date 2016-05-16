
#include <slib.h>

struct big_integer
{
    u64* Parts;

    big_integer& operator=(u64);
    big_integer& operator=(u32);
    big_integer& operator=(big_integer&);

    big_integer();
    big_integer(u64);        
    big_integer(big_integer&);
    ~big_integer();
};

struct overflow_int
{
    u64 Result;
    u64 Overflow;
};

internal size_t
BigIntegerCount(big_integer& big)
{
    size_t Result = buffer_count(big.Parts);

    while(Result > 1 && big.Parts[Result-1] == 0)
    {
        --Result;
    }

    return Result;
}

big_integer::big_integer()
{
    this->Parts = 0;
    buffer_push(this->Parts, 0);
}

big_integer::big_integer(u64 X)
{
    this->Parts = 0;
    buffer_push(this->Parts, X);
}

big_integer::big_integer(big_integer& big)
{
    this->operator=(big);
}

big_integer::~big_integer()
{
    if(this->Parts)
    {
        buffer_free(this->Parts);
        this->Parts = {};
    }
}

//u64 max: 18,446,744,073,709,551,615
//18 446 744 073 709 551 615
//10 000 000 000 000 000 000
//max power of 10 that fits in 64 bits
#define BaseTenOverflow 10000000000000000000

internal overflow_int
AddWithOverflow(u64 X, u64 Y)
{
    u64 XDistanceFromMax = BaseTenOverflow - X;

    overflow_int OverflowInt = {};

    OverflowInt.Result = X+Y;

    if(Y >= XDistanceFromMax)
    {
        OverflowInt.Overflow = 1;
        OverflowInt.Result = Y - XDistanceFromMax;
    }
    else
    {
        OverflowInt.Result = X+Y;
    }

    return OverflowInt;
}

internal overflow_int
AddWithOverflow(overflow_int X, u64 Y)
{
    u64 XDistanceFromMax = BaseTenOverflow - X.Result;

    if(Y > XDistanceFromMax)
    {
        X.Overflow += 1;
        X.Result = Y - XDistanceFromMax;
    }
    else
    {
        X.Result += Y;
    }

    return X;
}

inline b32
operator==(big_integer& X, big_integer& Y)
{
    b32 Result = 0;

    size_t XCount = BigIntegerCount(X);
    size_t YCount = BigIntegerCount(Y);
    if(XCount == YCount)
    {
        for(u32 PartIndex = 0;
            PartIndex < XCount;
            ++PartIndex)
        {
            if(X.Parts[PartIndex] != Y.Parts[PartIndex])
            {
                break;
            }
        }

        Result = 1;
    }

    return Result;
}

inline b32
operator==(big_integer& X, u64 Y)
{
    b32 Result = 0;

    size_t XPartCount = BigIntegerCount(X);
    
    if(XPartCount == 1)
    {
        if(X.Parts[0] == Y)
        {
            Result = 1;
        }
    }

    return Result;
}

big_integer&
big_integer::operator=(u64 X)
{
    if(this->Parts)
    {
        buffer_free(this->Parts);
        this->Parts = {};
    }

    this->Parts = {};

    buffer_push(Parts, X);

    return *this;
}

big_integer&
big_integer::operator=(u32 X)
{
    return this->operator=((u64)X);
}

big_integer&
big_integer::operator=(big_integer& X)
{
    size_t XPartCount = BigIntegerCount(X);
    if(this->Parts)
    {
        buffer_free(this->Parts);
        this->Parts = {};
        buffer_grow(this->Parts, (u32)XPartCount);
    }
    else
    {
        buffer_grow(this->Parts, (u32)(XPartCount - BigIntegerCount(*this)));
    }

    for(u32 PartIndex = 0;
        PartIndex < XPartCount;
        ++PartIndex)
    {
        this->Parts[PartIndex] = X.Parts[PartIndex];
    }

    return *this;
}

inline big_integer&
operator+=(big_integer& X, u64 Y)
{
    overflow_int PartResult = {};
    PartResult.Overflow = Y;

    size_t XPartCount = BigIntegerCount(X);

    for(u32 PartIndex = 0;
        PartIndex < XPartCount;
        ++PartIndex)
    {
        PartResult = AddWithOverflow(X.Parts[PartIndex], PartResult.Overflow);
        X.Parts[PartIndex] = PartResult.Result;
    }

    if(PartResult.Overflow)
    {
        buffer_grow(X.Parts, 1);
        X.Parts[BigIntegerCount(X)-1] = PartResult.Overflow;
    }

    return X;
}

inline big_integer
operator+(big_integer X, u64 Y)
{
    big_integer Result = {};
    Result = X;

    Result += Y;

    return Result;
}

internal void
AddBigIntToBigInt(big_integer *X, big_integer *Y)
{
    big_integer *Bigger, *Smaller;

    b32 NeedsToSwap = false;

    size_t XPartCount = BigIntegerCount(*X);
    size_t YPartCount = BigIntegerCount(*Y);
    size_t BiggerPartCount;
    size_t SmallerPartCount;
    
    if(XPartCount >= YPartCount)
    {
        Bigger = X;
        Smaller = Y;
        BiggerPartCount = XPartCount;
        SmallerPartCount = YPartCount;
    }
    else
    {
        NeedsToSwap = true;
        Bigger = Y;
        Smaller = X;
        BiggerPartCount = YPartCount;
        SmallerPartCount = XPartCount;
    }

    overflow_int PartResult = {};

    for(u32 PartIndex = 0;
        PartIndex < BiggerPartCount;
        ++PartIndex)
    {
        PartResult = AddWithOverflow(Bigger->Parts[PartIndex],
                                     PartResult.Overflow);

        if(SmallerPartCount > PartIndex)
        {
            PartResult = AddWithOverflow(PartResult,
                                         Smaller->Parts[PartIndex]);
        }

        Bigger->Parts[PartIndex] = PartResult.Result;
    }

    if(PartResult.Overflow)
    {
        ++BiggerPartCount;
        buffer_grow(Bigger->Parts, 1);
        Bigger->Parts[BiggerPartCount-1] = PartResult.Overflow;
    }

    if(NeedsToSwap)
    {
        X = Bigger;
        Y = Smaller;
    }
}

big_integer
operator+(big_integer X, big_integer Y)
{
    AddBigIntToBigInt(&X, &Y);

    return X;
}

inline big_integer&
operator+=(big_integer& X, big_integer& Y)
{
    AddBigIntToBigInt(&X, &Y);

    return X;
}

inline big_integer&
operator--(big_integer& X)
{
    size_t XPartCount = BigIntegerCount(X);
    if(X.Parts[XPartCount - 1])
    {
        --X.Parts[XPartCount - 1];
    }
    else if(XPartCount > 1)
    {
        Assert(!"true subtraction not actually implemented yet.");
    }
    else
    {
        Assert(!"Cannot subtract from a zero big_integer (negatives not yet implemented)");
    }

    return X;
}

inline big_integer
operator*(big_integer X, u64 Y)
{
    big_integer XValue = {};

    XValue = X;

    for(u32 IterationIndex = 0;
        IterationIndex < Y;
        ++IterationIndex)
    {
        X += XValue;
    }
}

void
MultBigIntToBigInt(big_integer& X, big_integer& Y)
{
    b32 StopAdding = (Y==0);

    big_integer XValue = {};
    big_integer YValue = {};

    YValue = Y;
    XValue = X;

    X = (u64)0;

    while(!StopAdding)
    {
        X += XValue;
        --YValue;
        StopAdding = (YValue==0);
    }
}

inline big_integer
operator*(big_integer X, big_integer Y)
{
    MultBigIntToBigInt(X, Y);

    return X;
}

inline big_integer&
operator*=(big_integer& X, big_integer& Y)
{
    MultBigIntToBigInt(X, Y);

    return X;
}

inline b32
operator>(big_integer X, u64 Y)
{
    b32 Result = false;

    if(BigIntegerCount(X) > 1)
    {
        Result = true;
    }
    else
    {
        Result = X.Parts[0] > Y;
    }

    return Result;
}

inline b32
operator<(big_integer X, big_integer Y)
{
    b32 Result = false;
    
    size_t XPartCount = BigIntegerCount(X);
    size_t YPartCount = BigIntegerCount(Y);
    if(XPartCount < YPartCount)
    {
        Result = true;
    }
    else if (XPartCount == YPartCount)
    {
        for(s32 PartIndex = (s32)XPartCount-1;
            PartIndex >= 0;
            --PartIndex)
        {
            if(X.Parts[PartIndex] < Y.Parts[PartIndex])
            {
                Result = true;
                break;
            }
            else if(X.Parts[PartIndex] > Y.Parts[PartIndex])
            {
                break;
            }
        }
    }

    return Result;
}

void
NumGoesIntoBigNum(big_integer *X, u64 Y)
{
    big_integer Test = {}, XValue = {};
    Test = (u64)0;
    XValue = *X;
    *X = (u64)0;

    while(Test < XValue)
    {
        *X += 1;
        Test += Y;
    }

    --*X;
}

inline big_integer
operator/(big_integer X, u64 Y)
{
    NumGoesIntoBigNum(&X, Y);

    return X;
}

inline big_integer&
operator/=(big_integer& X, u64 Y)
{
    NumGoesIntoBigNum(&X, Y);

    return X;
}

internal void
PrintBignum(big_integer& X)
{
    size_t XPartCount = BigIntegerCount(X);

    printf("%llu", X.Parts[XPartCount - 1]);
    
    for(s32 PartIndex = (s32)XPartCount - 2;
        PartIndex >= 0;
        --PartIndex)
    {
        printf("%019llu", X.Parts[PartIndex]);
    }
    printf("\n");
}
