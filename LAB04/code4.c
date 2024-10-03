#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int value = 100;
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        value += 10;
    }
    else if (pid > 0)
    {
        value -= 5;
    }
    printf("Value = %d.  my pid= %d\n", value, getpid());
    return 0;
}
