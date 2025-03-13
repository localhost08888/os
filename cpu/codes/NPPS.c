#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
    char pname[20];
    int at, bt, orig_bt;
    int ct, tat, wt;
    int priority;
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
        p[i].orig_bt = p[i].bt;

        printf("Enter priority (lower number indicates higher priority): ");
        scanf("%d", &p[i].priority);
    }
}

int find_next_process(Process p[], int n, int time)
{
    int highest_priority = 9999;
    int idx = -1;
    for (int i = 0; i < n; i++)
    {
        if (p[i].at <= time && p[i].bt > 0)
        {
            if (p[i].priority < highest_priority)
            {
                highest_priority = p[i].priority;
                idx = i;
            }
        }
    }
    return idx;
}

void simulate_priority(Process p[], int n)
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

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].orig_bt;
        p[idx].bt = 0;
        completed++;

        time += 2;
    }
}

void print_output(Process p[], int n)
{
    float avg_tat = 0, avg_wt = 0;
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%s\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pname, p[i].at, p[i].orig_bt, p[i].priority,
               p[i].ct, p[i].tat, p[i].wt);
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time = %.2f\n", avg_wt / n);
}

void print_gantt_chart(Process p[], int n)
{
    Process proc[n];
    for (int i = 0; i < n; i++)
    {
        proc[i] = p[i];
        proc[i].bt = proc[i].orig_bt;
    }

    printf("\nGantt Chart:\n");
    int time = 0, completed = 0;

    while (completed < n)
    {
        int idx = find_next_process(proc, n, time);
        if (idx == -1)
        {
            printf("| Idle (%d-%d) ", time, time + 1);
            time++;
        }
        else
        {

            printf("| %s (%d-%d) ", proc[idx].pname, time, time + proc[idx].bt);
            time += proc[idx].bt;

            proc[idx].bt = 0;
            completed++;

            printf("| I/O (%d-%d) ", time, time + 2);
            time += 2;
        }
    }
    printf("|\n");
}

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];

    accept_info(p, n);
    simulate_priority(p, n);
    print_output(p, n);
    print_gantt_chart(p, n);

    return 0;
}
