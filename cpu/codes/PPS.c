#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define IO_WAIT 2
#define MIN_NEXT_BURST 1    
#define MAX_NEXT_BURST 5     

typedef struct 
{
    char pname[20];           
    int at;                  
    int burst;                 
    int orig_burst;           
    int priority;              
    int ct;                   
    int tat;                  
    int wt;                 
    bool inIO;                
    int io_remaining;         
    bool finished;           
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
        scanf("%d", &p[i].burst);

        p[i].orig_burst = p[i].burst;    
        
        printf("Enter priority (lower number = higher priority): ");
        scanf("%d", &p[i].priority);
        
        p[i].inIO = false;
        p[i].io_remaining = 0;
        p[i].finished = false;
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
    }
}

   
int find_highest_priority(Process p[], int n, int time) 
{
    int idx = -1;
    int best_priority = 9999;
    for (int i = 0; i < n; i++)
     {
        if (p[i].at <= time && !p[i].inIO && !p[i].finished && p[i].burst > 0)
         {
            if (p[i].priority < best_priority) 
            {
                best_priority = p[i].priority;
                idx = i;
            }
        }
    }
    return idx;
}

   
void simulate_preemptive_priority(Process p[], int n)
 {
    int time = 0;
    int completed = 0;
    int total_tat = 0, total_wt = 0;
      
    typedef struct 
    {
        char label[20];
        int start;
        int end;
    } Segment;
    Segment gantt[1000];
    int segCount = 0;
      
    while (completed < n)
     {
        for (int i = 0; i < n; i++) 
        {
            if (p[i].inIO)
             {
                p[i].io_remaining--;
                if (p[i].io_remaining <= 0)
                 {
                    p[i].inIO = false;
                    int nextBurst = (rand() % MAX_NEXT_BURST) + MIN_NEXT_BURST;
                    p[i].burst = nextBurst;
                }
            }
        }
        
        int idx = find_highest_priority(p, n, time);
        if (idx == -1)
         {
            int idleStart = time;
            time++;
            gantt[segCount].start = idleStart;
            gantt[segCount].end = time;
            snprintf(gantt[segCount].label, sizeof(gantt[segCount].label), "Idle");
            segCount++;
            continue;
        }
        
        if (segCount == 0 || (segCount > 0 && strcmp(gantt[segCount-1].label, p[idx].pname) != 0)) 
        {
            gantt[segCount].start = time;
            snprintf(gantt[segCount].label, sizeof(gantt[segCount].label), "%s", p[idx].pname);
        }
        
        p[idx].burst--;
        time++;
          
        if (p[idx].burst == 0) 
        {
            gantt[segCount].end = time;
            segCount++;
            p[idx].finished = true;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].orig_burst;
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            completed++;
        }
    }
    
    printf("\nGantt Chart:\n");
    for (int i = 0; i < segCount; i++)
     {
        printf("| %s (%d-%d) ", gantt[i].label, gantt[i].start, gantt[i].end);
    }
    printf("|\n");
    
    printf("\nProcess Table:\n");
    printf("PName\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
     {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pname, p[i].at, p[i].orig_burst, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }
    
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

int main() 
{
    srand(time(0));  
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];
    accept_info(p, n);
    simulate_preemptive_priority(p, n);
    return 0;
}
