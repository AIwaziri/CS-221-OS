#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define INITIAL_BALANCE 100

int balance = INITIAL_BALANCE;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void withdraw(int amount)
{
    pthread_mutex_lock(&mutex);
    if (balance >= amount)
    {
        balance -= amount;
        printf("Withdrew %d, new balance: %d\n", amount, balance);
    }
    else
    {
        printf("Insufficient funds for withdrawal of %d, balance: %d\n", amount, balance);
    }
    pthread_mutex_unlock(&mutex);
}

void deposit(int amount)
{
    pthread_mutex_lock(&mutex);
    balance += amount;
    printf("Deposited %d, new balance: %d\n", amount, balance);
    pthread_mutex_unlock(&mutex);
}

void *transaction(void *arg)
{
    for (int i = 0; i < 100; i++)
    {
        int transaction_type = rand() % 2;
        int amount = rand() % 100;
        if (transaction_type == 0)
        {
            withdraw(amount);
        }
        else
        {
            deposit(amount);
        }
    }
    return NULL;
}

int main()
{
    pthread_t deposit_thread, withdraw_thread;
    pthread_create(&deposit_thread, NULL, transaction, NULL);
    pthread_create(&withdraw_thread, NULL, transaction, NULL);
    pthread_join(deposit_thread, NULL);
    pthread_join(withdraw_thread, NULL);
    printf("Final balance: %d\n", balance);
    return 0;
}