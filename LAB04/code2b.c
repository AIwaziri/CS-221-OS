#include <stdio.h>
#include <unistd.h>

int main()
{
    char *programName = "exc1";
    char *pathName = "/Users/aiwaziri/PycharmProjects/GitHub/CS-221-OS/LAB04/exc1";

    printf("Before calling exec(), PID: %d\n", getpid());
    execlp(pathName, programName, NULL);
    printf("After calling exec(), PID: %d\n", getpid());
    return 0;
}