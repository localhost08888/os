#include <stdio.h>
#include <stdbool.h>

#define MAX 30

int main() {
    int n, i, j, min_bt, min_index;
    int p[MAX], at[MAX], bt[MAX], ct[MAX], wt[MAX], tat[MAX], completed[MAX] = {0};
    float awt = 0, atat = 0;
    int gantt_process[MAX], gantt_time[MAX], gantt_count = 0; // Arrays for Gantt Chart

    // Input: Number of Processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Taking input for process numbers
    printf("Enter the process numbers: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    // Taking input for arrival times of processes
    printf("Enter the arrival time for each process: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    // Taking input for burst times of processes
    printf("Enter the burst time for each process: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    // Sorting processes based on arrival time using Bubble Sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                // Swap arrival times
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap burst times
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap process IDs
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Start execution based on SJF logic
    int time = 0, completed_count = 0;
    while (completed_count < n) {
        min_bt = 9999;
        min_index = -1;

        // Find the shortest job available at current time
        for (j = 0; j < n; j++) {
            if (!completed[j] && at[j] <= time) {
                if (bt[j] < min_bt) {
                    min_bt = bt[j];
                    min_index = j;
                }
            }
        }

        if (min_index == -1) {
            // If no process is available, CPU remains idle
            gantt_process[gantt_count] = -1;  // Represent idle state
            gantt_time[gantt_count++] = time;
            time++;
        } else {
            // Execute the selected process
            time += bt[min_index];
            ct[min_index] = time;
            completed[min_index] = 1;
            completed_count++;

            // Store process execution for Gantt Chart
            gantt_process[gantt_count] = p[min_index];
            gantt_time[gantt_count++] = time;
        }
    }

    // Calculate TAT and WT
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        atat += tat[i];

        wt[i] = tat[i] - bt[i];
        awt += wt[i];
    }

    awt /= n;
    atat /= n;

    // Display Results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", awt);
    printf("\nAverage Turnaround Time: %.2f\n", atat);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");

    // Print upper border
    printf(" ");
    for (i = 0; i < gantt_count; i++) {
        printf("--------");
    }
    printf("\n|");

    // Print process execution
    for (i = 0; i < gantt_count; i++) {
        if (gantt_process[i] == -1) {
            printf(" Idle  |");
        } else {
            printf(" P%d  |", gantt_process[i]);
        }
    }

    // Print lower border
    printf("\n ");
    for (i = 0; i < gantt_count; i++) {
        printf("--------");
    }

    // Print timeline
    printf("\n0");
    for (i = 0; i < gantt_count; i++) {
        printf("\t%d", gantt_time[i]);
    }
    printf("\n");

    return 0;
}
 
