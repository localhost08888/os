  #include <stdio.h> 
#define MAX 30 
 
int main()  
{ 
    int n, i, j, quantum; 
    int p[MAX], at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX], remaining_bt[MAX]; 
    int time = 0, completed = 0; 
    float awt = 0, atat = 0; 
 
    // Input: Number of Processes 
    printf("Enter the number of processes: "); 
    scanf("%d", &n); 
 
    // Taking input for process numbers 
    printf("Enter the process numbers: "); 
    for (i = 0; i < n; i++) 
     { 
        scanf("%d", &p[i]); 
    } 
 
    // Taking input for arrival times of processes 
    printf("Enter the arrival time for each process: "); 
    for (i = 0; i < n; i++)  
    { 
        scanf("%d", &at[i]); 
    } 
 
    // Taking input for burst times of processes 
    printf("Enter the burst time for each process: "); 
    for (i = 0; i < n; i++) 
     { 
        scanf("%d", &bt[i]); 
        remaining_bt[i] = bt[i]; // Initialize remaining burst time 
    } 
 
    // Taking time quantum input 
    printf("Enter the time quantum: "); 
    scanf("%d", &quantum); 
  
    // Round Robin Scheduling 
    int queue[MAX], front = 0, rear = 0; 
    int visited[MAX] = {0}; // To track if a process is already in queue 
 
    queue[rear++] = 0; // Start with the first process 
    visited[0] = 1; 
 
    while (completed != n) 
     { 
        int index = queue[front++]; 
         
        // Execute the process for `quantum` or remaining burst time 
        int exec_time = (remaining_bt[index] > quantum) ? quantum : remaining_bt[index]; 
        time += exec_time; 
        remaining_bt[index] -= exec_time; 
 
        // Check if new processes have arrived and add them to the queue 
        for (i = 0; i < n; i++)  
        { 
            if (at[i] <= time && !visited[i] && remaining_bt[i] > 0) 
             { 
                queue[rear++] = i; 
                visited[i] = 1; 
            } 
        } 
 
        // If process is not completed, put it back in queue 
        if (remaining_bt[index] > 0)  
        { 
            queue[rear++] = index; 
        }  
        else  
        { // If process is completed, store completion time 
            ct[index] = time; 
            completed++; 
        } 
    } 
 
    // Calculate Turnaround Time (TAT) and Waiting Time (WT) 
    for (i = 0; i < n; i++)  
    { 
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
    for (i = 0; i < n; i++) 
     {  
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]); 
    } 
 
    // Printing average values 
    printf("\nAverage Waiting Time: %.2f", awt); 
    printf("\nAverage Turnaround Time: %.2f\n", atat); 
 
    return 0; 
} 
