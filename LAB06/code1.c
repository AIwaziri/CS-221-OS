#include <stdio.h>
#define MAX_PROC 3

struct Process
{
    int burst_t,
        wait_t,
        tat;
};

void Calc_Avg_WT_TAT(struct Process P[])
{
    float total_wait_t = 0.0;
    float total_tat = 0.0;

    P[0].wait_t = 0;
    P[0].tat = P[0].burst_t;
    total_tat += P[0].tat;

    printf("P[0] BT: %d WT: %d TAT: %d Total WT: %.2f Total TAT: %.2f\n", P[0].burst_t, P[0].wait_t, P[0].tat, total_wait_t, total_tat);

    for (int i = 1; i < MAX_PROC; i++)
    {
        P[i].wait_t = P[i - 1].wait_t + P[i - 1].burst_t;
        total_wait_t += P[i].wait_t;

        P[i].tat = P[i].wait_t + P[i].burst_t;
        total_tat += P[i].tat;

        printf("P[%d] BT: %d WT: %d TAT: %d Total WT: %.2f Total TAT: %.2f\n", i, P[i].burst_t, P[i].wait_t, P[i].tat, total_wait_t, total_tat);
    }

    printf("Average WT: %.2f\n", total_wait_t / MAX_PROC);
    printf("Average TAT: %.2f\n", total_tat / MAX_PROC);
}

int main()
{
    struct Process P[MAX_PROC] = {{25, 0, 0}, {4, 0, 0}, {3, 0, 0}};
    Calc_Avg_WT_TAT(P);
    return 0;
}