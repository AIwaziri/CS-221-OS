#include <stdio.h>
#include <unistd.h>
#define MAX_ITER 2

int main()
{
    for (int i = 1; i < MAX_ITER; i++)
    {
        fork();
    }
    return 0;
}