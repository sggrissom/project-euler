
#include <stdio.h>
#include <stdlib.h>

#include <slib.h>


//only works for odd numbers which is fine for this particular problem
internal u32
DiagnoalSpiralSum(u32 SpiralSize)
{
    u32 Result = 1;
    u32 Depth = 1;
    u32 LastValue = 1;

    u32 SpiralDepth = (SpiralSize + 1) / 2;

    while(Depth < SpiralDepth)
    {
        u32 LevelResult = 4 * LastValue + Depth * 20;
        LastValue = LastValue + Depth * 8;
        Result += LevelResult;
        ++Depth;
    }

    return Result;
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

//    u32 x = sg_atoi(cx);
//    u32 y = sg_atoi(cy);

    printf("%d\n", DiagnoalSpiralSum(1001));

    return 0;
}
