#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_THREAD 10

void *welcome(void *arg)
{
    printf("Thread %lu: Welcome to Madinah!\n", (unsigned long)pthread_self());
    pthread_exit(NULL);
}

int main()
{
    int num_threads;
    printf("Enter the number of threads to create (max %d): ", MAX_THREAD);
    scanf("%d", &num_threads);

    if (num_threads > MAX_THREAD)
    {
        printf("Number of threads exceeds the maximum limit of %d. Setting to %d.\n", MAX_THREAD, MAX_THREAD);
        num_threads = MAX_THREAD;
    }
    else if (num_threads <= 0)
    {
        printf("Number of threads must be greater than 0. Exiting.\n");
        return 1;
    }

    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, welcome, NULL);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}