#include <stdio.h>
#include <limits.h>

#define MAX 30

int main() {
    int n, i;
    int p[MAX], at[MAX], bt[MAX], ct[MAX], wt[MAX], tat[MAX], priority[MAX], remaining_bt[MAX];
    int completed = 0, time = 0, minPriority, idx;
    float awt = 0, atat = 0;
    int isCompleted[MAX] = {0}; 
    int ganttChart[MAX * 2], ganttTime[MAX * 2], gcIndex = 0;

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
        remaining_bt[i] = bt[i];  // Initialize remaining burst time
    }

    printf("Enter priority for each process (lower number = higher priority): ");
    for (i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    // Start processing
    while (completed < n) {
        minPriority = INT_MAX;
        idx = -1;

        // Find the highest-priority process that has arrived
        for (i = 0; i < n; i++) {
            if (at[i] <= time && !isCompleted[i] && priority[i] < minPriority) {
                minPriority = priority[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++; // If no process is available, increase time (CPU idle)
        } else {
            // Store process execution in Gantt Chart
            if (gcIndex == 0 || ganttChart[gcIndex - 1] != p[idx]) {
                ganttChart[gcIndex] = p[idx];
                ganttTime[gcIndex] = time;
                gcIndex++;
            }

            remaining_bt[idx]--; // Execute the process for 1 unit of time
            time++; 

            // If the process finishes execution
            if (remaining_bt[idx] == 0) {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                awt += wt[idx];
                atat += tat[idx];
                isCompleted[idx] = 1; 
                completed++;
            }
        }
    }

    awt /= n;
    atat /= n;

    // Output process details
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i], at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", awt);
    printf("\nAverage Turnaround Time: %.2f\n", atat);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    
    // Print top border
    printf(" ");
    for (i = 0; i < gcIndex; i++) {
        printf("-------");
    }
    printf("\n|");

    // Print process execution sequence
    for (i = 0; i < gcIndex; i++) {
        printf(" P%d |", ganttChart[i]);
    }

    // Print bottom border
    printf("\n ");
    for (i = 0; i < gcIndex; i++) {
        printf("-------");
    }

    // Print time labels
    printf("\n0");
    for (i = 0; i < gcIndex; i++) {
        printf("\t%d", ganttTime[i]);
    }
    printf("\t%d\n", time);

    return 0;
}
