#include <stdio.h>

#define MAX_PROC 5

struct Process
{
    int pid;
    int burst_t;
    int wait_t;
    int tat;
};

void sort_by_burst_time(struct Process P[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (P[j].burst_t > P[j + 1].burst_t)
            {
                struct Process temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }
}

void Calc_Avg_WT_TAT(struct Process P[], int n)
{
    float total_wait_t = 0.0;
    float total_tat = 0.0;

    P[0].wait_t = 0;
    P[0].tat = P[0].burst_t;
    total_tat += P[0].tat;

    for (int i = 1; i < n; i++)
    {
        P[i].wait_t = P[i - 1].wait_t + P[i - 1].burst_t;
        total_wait_t += P[i].wait_t;

        P[i].tat = P[i].wait_t + P[i].burst_t;
        total_tat += P[i].tat;
    }

    printf("PID\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n", P[i].pid, P[i].burst_t, P[i].wait_t, P[i].tat);
    }

    printf("Average WT: %.2f\n", total_wait_t / n);
    printf("Average TAT: %.2f\n", total_tat / n);
}

int main()
{
    struct Process P[MAX_PROC] = {
        {1, 6, 0, 0},
        {2, 8, 0, 0},
        {3, 7, 0, 0},
        {4, 3, 0, 0},
        {5, 4, 0, 0}};

    int n = MAX_PROC;

    sort_by_burst_time(P, n);

    Calc_Avg_WT_TAT(P, n);

    return 0;
}