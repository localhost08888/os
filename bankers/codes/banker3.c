#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10 // Maximum processes
#define MAX_R 10 // Maximum resources

int alloc[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R], avail[MAX_R];
int p, r; // Number of processes and resources

void input_data()
{
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &p, &r);

    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("\nEnter Available resources:\n");
    for (int i = 0; i < r; i++)
        scanf("%d", &avail[i]);
}

void display_state()
{
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
            printf("%d ", alloc[i][j]);
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("\nAvailable Resources: ");
    for (int i = 0; i < r; i++)
        printf("%d ", avail[i]);
    printf("\n");
}

bool is_safe()
{
    int work[MAX_R], finish[MAX_P] = {0}, safe_seq[MAX_P], count = 0;

    for (int i = 0; i < r; i++)
        work[i] = avail[i];

    while (count < p)
    {
        bool found = false;
        for (int i = 0; i < p; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < r; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == r)
                {
                    for (j = 0; j < r; j++)
                        work[j] += alloc[i][j];
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found)
        {
            printf("\nSystem is NOT SAFE!\n");
            return false;
        }
    }

    printf("\nSystem is SAFE!\nSafe Sequence: ");
    for (int i = 0; i < p; i++)
        printf("P%d ", safe_seq[i]);
    printf("\n");
    return true;
}

void request_resources()
{
    int proc, req[MAX_R];

    printf("\nEnter process number (0 to %d): ", p - 1);
    scanf("%d", &proc);

    printf("Enter resource request for P%d:\n", proc);
    for (int i = 0; i < r; i++)
        scanf("%d", &req[i]);

    for (int i = 0; i < r; i++)
    {
        if (req[i] > need[proc][i] || req[i] > avail[i])
        {
            printf("\nInvalid request! Exceeds need or available resources.\n");
            return;
        }
    }

    // Try allocation
    for (int i = 0; i < r; i++)
    {
        avail[i] -= req[i];
        alloc[proc][i] += req[i];
        need[proc][i] -= req[i];
    }

    if (!is_safe())
    { // Rollback if unsafe
        for (int i = 0; i < r; i++)
        {
            avail[i] += req[i];
            alloc[proc][i] -= req[i];
            need[proc][i] += req[i];
        }
        printf("Request denied - would lead to unsafe state.\n");
    }
    else
    {
        printf("Request granted.\n");
    }
}

int main()
{
    int choice;
    while (1)
    {
        printf("\nBanker's Algorithm Menu:\n"
               "1. Input Data\n"
               "2. Display State\n"
               "3. Check System Safety\n"
               "4. Request Resources\n"
               "5. Exit\n"
               "Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            input_data();
            break;
        case 2:
            display_state();
            break;
        case 3:
            is_safe();
            break;
        case 4:
            request_resources();
            break;
        case 5:
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
}
