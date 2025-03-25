 #include <stdio.h>
#include <stdbool.h>

#define MAX 30

int main() {
    int n, i, j;
    int p[MAX], at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX], remaining_bt[MAX];
    bool is_completed[MAX] = {false};
    int time = 0, completed = 0;
    float awt = 0, atat = 0;

    int gantt_process[MAX * 2], gantt_time[MAX * 2], gantt_count = 0;

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
        remaining_bt[i] = bt[i]; // Initialize remaining burst time
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

                // Swap remaining burst times
                temp = remaining_bt[j];
                remaining_bt[j] = remaining_bt[j + 1];
                remaining_bt[j + 1] = temp;

                // Swap process IDs to maintain order
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int prev_process = -1;

    // Preemptive SJF Scheduling (SRTF)
    while (completed != n) {
        int min_index = -1;
        int min_bt = 9999;

        // Find the process with the shortest remaining burst time that has arrived
        for (i = 0; i < n; i++) {
            if (at[i] <= time && !is_completed[i] && remaining_bt[i] < min_bt) {
                min_bt = remaining_bt[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            // No process available to execute, move time forward
            if (prev_process != -1) {
                gantt_process[gantt_count] = -1; // Represent idle time
                gantt_time[gantt_count++] = time;
            }
            time++;
            continue;
        }

        // Record Gantt Chart execution
        if (prev_process != p[min_index]) {
            gantt_process[gantt_count] = p[min_index];
            gantt_time[gantt_count++] = time;
        }

        // Execute the process for 1 unit of time
        remaining_bt[min_index]--;
        time++;

        // If the process completes execution
        if (remaining_bt[min_index] == 0) {
            ct[min_index] = time;  // Store completion time
            is_completed[min_index] = true;
            completed++;
        }

        prev_process = p[min_index];
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WT)
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i]; // TAT = CT - AT
        atat += tat[i];

        wt[i] = tat[i] - bt[i]; // WT = TAT - BT
        awt += wt[i];
    }

    // Calculate average waiting time and turnaround time
    awt /= n;
    atat /= n;

    // Display results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) { 
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // Printing average values
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
