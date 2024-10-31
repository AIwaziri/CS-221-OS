#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_ITER 100000
#define MAX_THREAD 2

int sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *add_one(void *arg)
{
    for (int i = 0; i < MAX_ITER; i++)
    {
        printf("Thread %ld: i=%d\n", pthread_self(), i);
        pthread_mutex_lock(&mutex);
        sum++;
        // pthread_mutex_unlock(&mutex);
    }
    printf("Thread %ld: MAX_ITER = %d\n", pthread_self(), MAX_ITER, sum);
    pthread_exit(0);
}
int main()
{
    pthread_t thread[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_create(&thread[i], NULL, add_one, NULL);
    }
    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(thread[i], NULL);
    }
    printf("Final value of sum = %d\n", sum);

    return 0;
}