 #include <stdio.h>

#define MAX 30

int main() 
{
    int n, i, j;
    int p[MAX], at[MAX], bt[MAX], ct[MAX], wt[MAX], tat[MAX];
    float awt = 0, atat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the process numbers: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    
    printf("Enter the arrival time for each process: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    
    printf("Enter the burst time for each process: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
              
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int time = 0;
    for (i = 0; i < n; i++) {
        if (time < at[i]) {
            time = at[i]; 
        }
        time += bt[i]; 
        ct[i] = time;  
    }

   
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        atat += tat[i];

        wt[i] = tat[i] - bt[i]; 
        awt += wt[i];
    }

   
    awt /= n;
    atat /= n;

    
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
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
