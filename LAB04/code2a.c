#include <stdio.h>
#include <unistd.h>

int main()
{
    char *progaramName = "ps";
    char *pathName = "/bin/ps";

    printf("Before calling  exec() \n");
    execlp(pathName, progaramName, NULL);
    printf("After calling  exec() \n");
    return 0;
}
