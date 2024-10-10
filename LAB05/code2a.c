#include <stdio.h>
#include <pthread.h>

#define MAX_THREAD 5

void *welcome(void *arg)
{
    printf("Thread %lu: Welcome to Madinah!\n", (unsigned long)pthread_self());
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_create(&threads[i], NULL, welcome, NULL);
    }

    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}