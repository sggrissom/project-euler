
#include <stdio.h>
#include <stdlib.h>

#include <slib.h>

struct division_step
{
    u32 Left;
    u32 Result;
};

internal void
PrintDivisionSteps(division_step *DivisionHistory, s32 CycleStartIndex)
{   
    printf("0.");
    
    for(size_t ArrayIndex = 0;
        ArrayIndex < buffer_count(DivisionHistory);
        ++ArrayIndex)
    {
        if(CycleStartIndex == ArrayIndex)
        {
            printf("(");
        }
        division_step Step = DivisionHistory[ArrayIndex];
        printf("%01d", Step.Result);
    }

    if(CycleStartIndex >= 0)
    {
        printf(")");
    }
}

internal s32
IsEntryInArray(division_step *DivisionHistory, division_step DivisionStep)
{
    s32 Result = -1;

    for(size_t ArrayIndex = 0;
        ArrayIndex < buffer_count(DivisionHistory);
        ++ArrayIndex)
    {
        division_step Step = DivisionHistory[ArrayIndex];

        if(Step.Left == DivisionStep.Left && Step.Result == DivisionStep.Result)
        {
            Result = (s32)ArrayIndex;
            break;
        }
    }

    return Result;
}

internal u32
FractionRecurringCycle(u32 x, u32 y)
{
    Assert(y > x);
    division_step DivisionStep = {1, 0};
    division_step PreviousDivisionStep = {x * 10, 0};
    s32 CycleStartIndex = -1;
    
    division_step *DivisionHistory = 0;

    while(CycleStartIndex < 0 && DivisionStep.Left > 0)
    {
        DivisionStep.Result = PreviousDivisionStep.Left / y;
        DivisionStep.Left = 10 * (PreviousDivisionStep.Left - (DivisionStep.Result * y));

        CycleStartIndex = IsEntryInArray(DivisionHistory, DivisionStep);
        if(CycleStartIndex < 0)
        {
            buffer_push(DivisionHistory, DivisionStep);
        }

        PreviousDivisionStep = DivisionStep;
    }

//    printf("%d/%d = ", x, y);
//    PrintDivisionSteps(DivisionHistory, CycleStartIndex);

    u32 CycleCount = CycleStartIndex < 0 ? 0 : buffer_count(DivisionHistory) - CycleStartIndex;
//    printf(" -- %d", CycleCount);
//    printf("\n");

    return CycleCount;
}

s32 main(s32 argc, char *argv[])
{
    char *cx = "3", *cy = "1";
    if (argc == 2)
    {
        cx = argv[1];
    } else if (argc == 3) {
        cx = argv[1];
        cy = argv[2];
    }

    u32 x = sg_atoi(cx);
    u32 y = sg_atoi(cy);

    u32 MaxCycleCount = 0;
    u32 MaxIndex = 0;
    u32 TestNumber = 2;
    
    while(TestNumber < 1000)
    {
        u32 CycleCount = FractionRecurringCycle(1, TestNumber++);

        if(CycleCount > MaxCycleCount)
        {
            MaxCycleCount = CycleCount;
            MaxIndex = TestNumber;
        }
    }

    printf("%d\n", MaxIndex-1);

    return 0;
}
