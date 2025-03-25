#include <stdio.h>

#define MAX 30

int main() {
    int n, i, j;
    int p[MAX], at[MAX], bt[MAX], ct[MAX], wt[MAX], tat[MAX], priority[MAX];
    float awt = 0, atat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter process numbers: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    printf("Enter arrival time for each process: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("Enter burst time for each process: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    printf("Enter priority for each process (lower number means higher priority): ");
    for (i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    // Sort processes based on arrival time, then priority if arrival times are the same
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1] || (at[j] == at[j + 1] && priority[j] > priority[j + 1])) {
                // Swap arrival time
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap burst time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap priority
                temp = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp;

                // Swap process numbers
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int time = 0, completed = 0;
    int isCompleted[MAX] = {0}; // Track completed processes

    while (completed < n) {
        int minPriority = 9999, idx = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && !isCompleted[i]) {
                if (priority[i] < minPriority) {
                    minPriority = priority[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
        } else {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            awt += wt[idx];
            atat += tat[idx];
            isCompleted[idx] = 1; 
            completed++;
        }
    }

    awt /= n;
    atat /= n;

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i], at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", awt);
    printf("\nAverage Turnaround Time: %.2f\n", atat);

    printf("\nGantt Chart:\n");
    printf(" ");
    for (i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n|");

    time = 0;
    for (i = 0; i < n; i++) {
        if (time < at[i]) {
            printf(" Idle |");
            time = at[i];
        }
        printf(" P%d |", p[i]);
        time += bt[i];
    }

    printf("\n ");
    for (i = 0; i < n; i++) {
        printf("-------");
    }

    printf("\n0");
    time = 0;
    for (i = 0; i < n; i++) {
        if (time < at[i]) {
            printf("\t%d", at[i]);
            time = at[i];
        }
        time += bt[i];
        printf("\t%d", time);
    }
    printf("\n");

    return 0;
}
