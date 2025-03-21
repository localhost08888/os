#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char pname[20];
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int bt1;
} Process;

void accept_info(Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter process name: ");
        scanf("%s", p[i].pname);

        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);

        printf("Enter first CPU burst time: ");
        scanf("%d", &p[i].bt);

        p[i].bt1 = p[i].bt;
    }
}

void sort_by_arrival(Process p[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void simulate_fcfs(Process p[], int n)
{
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        if (time < p[i].at)
        {
            time = p[i].at;
        }
        time += p[i].bt1;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time += 2;

        p[i].bt1 = rand() % 10 + 1;
    }
}

void print_output(Process p[], int n)
{
    float avg_tat = 0, avg_wt = 0;
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pname, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time = %.2f\n", avg_wt / n);
}

void print_gantt_chart(Process p[], int n)
{
    printf("\nGantt Chart:\n");
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        if (time < p[i].at)
        {
            printf("| Idle (%d-%d) ", time, p[i].at);
            time = p[i].at;
        }
        printf("| %s (%d-%d) ", p[i].pname, time, time + p[i].bt);
        time += p[i].bt;
        printf("| I/O (%d-%d) ", time, time + 2);
        time += 2;
    }
    printf("|\n");
}

int main()
{
    srand(time(0));
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    accept_info(p, n);
    sort_by_arrival(p, n);
    simulate_fcfs(p, n);
    print_output(p, n);
    print_gantt_chart(p, n);

    return 0;
}