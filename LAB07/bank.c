#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_TRANSACTION 10

int balance = 1000;

void *deposit(int amount)
{
    printf("+ Thread %ld: Deposit %d\n", pthread_self(), amount);
    balance += amount;
}
void *withdraw(int amount)
{
    if (balance >= amount)
    {
        printf("- Thread %ld: Withdraw %d\n", pthread_self(), amount);
        balance -= amount;
    }
    else
    {
        printf("- Thread %ld: Insufficient funds\n", pthread_self());
    }
}
void *transaction(void *arg)
{
    for (int i = 0; i < MAX_TRANSACTION; i++)
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
