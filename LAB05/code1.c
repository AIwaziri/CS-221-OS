#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_ITER 5

void *MyTurn(void *arg)
{
    for (int i = 1; i <= MAX_ITER; i++)
    {
        sleep(2);
        printf("My Turn i= %d\n", i);
    }
    pthread_exit(0);
}

void YourTurn()
{
    for (int i = 1; i <= MAX_ITER; i++)
    {
        sleep(1);
        printf("Your Turn %d\n", i);
    }
}
int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, MyTurn, NULL);
    pthread_join(thread, NULL);
    YourTurn();
    return 0;
}