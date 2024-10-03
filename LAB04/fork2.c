#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork Faild");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child Process.\n");
        printf("return of the fork = %d\n", pid);
        printf("Current pid = %d\n", getpid());
        printf("Parent pid = %d\n", getppid());

        execlp("/bin/ls", "ls", NULL);
        printf("hi");
    }
    else
    {
        printf("Child Complete.\n");
        printf("Parent Process.\n");
        printf("return of the fork = %d\n", pid);
        printf("Current pid = %d\n", getpid());
        printf("Parent pid = %d\n", getppid());
    }
    printf("Printing after the if. pid = %d\n", getpid());
    return 0;
}