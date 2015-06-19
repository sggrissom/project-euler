
#include <stdio.h>

int fib(int x)
{
    if(x<=1) return 1;
    if(x<=2) return 2;

    return fib(x-1) + fib(x-2);
}

int main()
{
    int i = 0, sum = 0, lastFib = 0;

    while(lastFib < 4000000)
    {
        lastFib = fib(i++);
        if((lastFib & 1) == 0)
        {
            sum += lastFib;
        }
    }
    
    printf("fib sum: %d\n\r", sum);

    return 0;
}
