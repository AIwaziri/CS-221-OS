#include <stdio.h>
#include <unistd.h>
#define MAX_ITER 2

int main()
{
    for (int i = 1; i <= MAX_ITER; i++)
    {
        fork();
        printf("Welcome to Madinah! My pid is %d.\n", getpid());
    }
    return 0;
}