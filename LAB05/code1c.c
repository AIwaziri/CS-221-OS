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

void *YourTurn(void *arg)
{
    for (int i = 1; i <= MAX_ITER; i++)
    {
        sleep(1);
        printf("Your Turn %d\n", i);
    }
    pthread_exit(0);
}

int main()
{
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, MyTurn, NULL);
    pthread_create(&thread2, NULL, YourTurn, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}