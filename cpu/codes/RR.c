#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char pname[20];
    int at, bt, ct, tat, wt, bt1;
} Process;

void accept_info(Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter process name: ");
        scanf("%s", p[i].pname);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);
        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);
        p[i].bt1 = p[i].bt;
    }
}

void simulate_rr(Process p[], int n, int quantum)
{
    int time = 0, completed = 0;
    int queue[n], front = 0, rear = 0;
    int in_queue[n];
    for (int i = 0; i < n; i++)
        in_queue[i] = 0;

    for (int i = 0; i < n; i++)
    {
        if (p[i].at == 0)
        {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    while (completed < n)
    {
        if (front == rear)
        {
            time++;
            for (int i = 0; i < n; i++)
            {
                if (p[i].at == time && !in_queue[i])
                {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (p[idx].bt1 > quantum)
        {
            time += quantum;
            p[idx].bt1 -= quantum;
        }
        else
        {
            time += p[idx].bt1;
            p[idx].bt1 = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].bt1 > 0 && !in_queue[i])
            {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        if (p[idx].bt1 > 0)
        {
            queue[rear++] = idx;
        }
    }
}

void print_output(Process p[], int n)
{
    float avg_tat = 0, avg_wt = 0;
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i].pname, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time = %.2f\n", avg_wt / n);
}

int main()
{
    srand(time(0));
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    Process p[n];
    accept_info(p, n);
    simulate_rr(p, n, quantum);
    print_output(p, n);
    return 0;
}