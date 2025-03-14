#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES];
int num_processes, num_resources;

void acceptMatrices() 
{
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
		
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Max matrix:\n");
    for (int i = 0; i < num_processes; i++)
     {
        for (int j = 0; j < num_resources; j++)
       {
            scanf("%d", &max[i][j]);
        }
     }
}

// Function to display Allocation and Max matrices
void displayMatrices()
 {
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++)
       {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
}

int main() 
{
    int choice;

    while (1) 
    {
        printf("1.Accept Allocation and Max\n");
        printf("2.Display Allocation and Max\n");
        printf("3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                acceptMatrices();
                break;
            case 2:
                displayMatrices();
                break;
            case 3:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
