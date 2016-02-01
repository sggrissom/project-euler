
#include <slib.h>

struct big_integer
{
    u64* Parts;
    u32 PartCount;

    big_integer operator=(u64);
    big_integer operator=(u32);
    big_integer operator=(big_integer);

    //~big_integer();
};

struct overflow_int
{
    u64 Result;
    u64 Overflow;
};

/*
big_integer::~big_integer()
{
    free(this->Parts);
}
*/

internal overflow_int
AddWithOverflow(u64 X, u64 Y)
{
    u64 XDistanceFromMax = UINT64_MAX - X;

    overflow_int OverflowInt = {};

    OverflowInt.Result = X+Y;
    
    if(Y > XDistanceFromMax)
    {
        OverflowInt.Overflow = 1;
    }

    return OverflowInt;
}

internal overflow_int
AddWithOverflow(overflow_int X, u64 Y)
{
    u64 XDistanceFromMax = UINT64_MAX - X.Result;

    X.Result += Y;
    
    if(Y > XDistanceFromMax)
    {
        X.Overflow += 1;
    }

    return X;
}

inline b32
operator==(big_integer X, big_integer Y)
{
    b32 Result = 0;

    if(X.PartCount == Y.PartCount)
    {
        for(u32 PartIndex = 0;
            PartIndex < X.PartCount;
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
operator==(big_integer X, u64 Y)
{
    b32 Result = 0;

    if(X.PartCount == 1)
    {
        if(X.Parts[0] == Y)
        {
            Result = 1;
        }
    }
    
    return Result;
}

big_integer
big_integer::operator=(u64 X)
{
    this->PartCount = 1;
    this->Parts = (u64*)malloc(sizeof(u64));
    *this->Parts = X;

    return *this;
}

big_integer
big_integer::operator=(u32 X)
{
    return this->operator=((u64)X);
}

big_integer
big_integer::operator=(big_integer X)
{
    this->PartCount = X.PartCount;
    this->Parts = (u64*)malloc(sizeof(u64) * X.PartCount);
    for(u32 PartIndex = 0;
        PartIndex < X.PartCount;
        ++PartIndex)
    {
        this->Parts[PartIndex] = X.Parts[PartIndex];
    }
    
    return *this;
}

inline big_integer
operator+=(big_integer X, u64 Y)
{
    overflow_int PartResult = {};
    PartResult.Overflow = Y;
      
    for(u32 PartIndex = 0;
        PartIndex < X.PartCount;
        ++PartIndex)
    {
        PartResult = AddWithOverflow(X.Parts[PartIndex], PartResult.Overflow);
        X.Parts[PartIndex] = PartResult.Result;
    }

    if(PartResult.Overflow)
    {
        ++X.PartCount;
        X.Parts = (u64*)realloc(X.Parts, sizeof(u64) * X.PartCount);
        Assert(X.Parts);
        X.Parts[X.PartCount-1] = PartResult.Overflow;
    }

    return X;
}

inline big_integer
operator+(big_integer X, u64 Y)
{
    big_integer Result;
    Result = X;

    Result += Y;

    return Result;
}

inline big_integer
operator+(big_integer X, big_integer Y)
{
    big_integer Bigger = {}, Smaller = {};

    if(X.PartCount >= Y.PartCount)
    {
        Bigger = X;
        Smaller = Y;
    }
    else
    {
        Bigger = Y;
        Smaller = X;
    }

    overflow_int PartResult = {};
    
    for(u32 PartIndex = 0;
        PartIndex < Bigger.PartCount;
        ++PartIndex)
    {
        PartResult = AddWithOverflow(Bigger.Parts[PartIndex],
                                     PartResult.Overflow);

        if(Smaller.PartCount > PartIndex)
        {
            PartResult = AddWithOverflow(PartResult,
                                         Smaller.Parts[PartIndex]);
        }
        
        Bigger.Parts[PartIndex] = PartResult.Result;
    }

    if(PartResult.Overflow)
    {
        ++Bigger.PartCount;
        Bigger.Parts = (u64*)realloc(Bigger.Parts, sizeof(u64) * Bigger.PartCount);
        Assert(Bigger.Parts);
        Bigger.Parts[Bigger.PartCount-1] = PartResult.Overflow;
    }

    return Bigger;
}

inline big_integer
operator+=(big_integer X, big_integer Y)
{
    X = X + Y;
    return X;
}

inline big_integer
operator--(big_integer X)
{
    if(X.Parts[X.PartCount - 1])
    {
        --X.Parts[X.PartCount - 1];
    }
    else if(X.PartCount > 1)
    {
        --X.PartCount;
        X.Parts = (u64*)realloc(X.Parts, sizeof(u64) * X.PartCount);
        Assert(X.Parts);
        --X;
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
    big_integer XValue;

    XValue = X;
    
    for(u32 IterationIndex = 0;
        IterationIndex < Y;
        ++IterationIndex)
    {
        X += XValue;
    }
}

inline big_integer
operator*(big_integer X, big_integer Y)
{
    b32 StopAdding = (Y==0);

    big_integer Result;
    big_integer YValue;

    YValue= Y;

    Result = (u64)0;
 
    while(!StopAdding)
    {
        Result += X;
        --YValue;
        StopAdding = (YValue==0);
    }

    return Result;
}

inline big_integer
operator*=(big_integer X, big_integer Y)
{
    X = X*Y;
    return X;
}
    
internal b32
BignumTest()
{
    big_integer Number, OtherNumber = {};
    Number = (u64)0;

    Assert(Number.PartCount == 1);

    Assert(Number == 0);
    
    Number += 30;

    Assert(Number == 30);

    OtherNumber = (u64)2;

    Number += OtherNumber;

    Assert(Number == 32);
    
    Number *= Number;
        
    Assert(Number == (32*32));
    Assert(OtherNumber == 2);

    --OtherNumber;

    Assert(OtherNumber == 1);

    return 1;
}
