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

        printf("Enter first CPU burst time: ");
        scanf("%d", &p[i].bt);

        p[i].bt1 = p[i].bt;
    }
}

int find_next_process(Process p[], int n, int time)
{
    int shortest = -1;
    for (int i = 0; i < n; i++)
    {
        if (p[i].bt1 > 0 && p[i].at <= time)
        {
            if (shortest == -1 || p[i].bt1 < p[shortest].bt1)
            {
                shortest = i;
            }
        }
    }
    return shortest;
}

void simulate_sjf(Process p[], int n)
{
    int time = 0, completed = 0;
    while (completed < n)
    {
        int idx = find_next_process(p, n, time);
        if (idx == -1)
        {
            time++;
            continue;
        }
        p[idx].bt1--;
        time++;
        if (p[idx].bt1 == 0)
        {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
            time += 2;
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

void print_gantt_chart(Process p[], int n)
{
    printf("\nGantt Chart:\n");
    int time = 0;
    while (1)
    {
        int idx = find_next_process(p, n, time);
        if (idx == -1)
        {
            printf("| Idle (%d-%d) ", time, time + 1);
            time++;
        }
        else
        {
            printf("| %s (%d-%d) ", p[idx].pname, time, time + 1);
            p[idx].bt1--;
            time++;
            if (p[idx].bt1 == 0)
            {
                printf("| I/O (%d-%d) ", time, time + 2);
                time += 2;
            }
        }
        int all_completed = 1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].bt1 > 0)
            {
                all_completed = 0;
                break;
            }
        }
        if (all_completed)
            break;
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
    simulate_sjf(p, n);
    print_output(p, n);
    print_gantt_chart(p, n);

    return 0;
}