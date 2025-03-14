#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

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

// Function to accept Available resources
void acceptAvailable() 
{
    printf("\nEnter Available resources:\n");
    for (int i = 0; i < num_resources; i++)
		 {
        scanf("%d", &available[i]);
    }
}

 
void calculateNeed() {
    for (int i = 0; i < num_processes; i++) 
		{
        for (int j = 0; j < num_resources; j++) 
				{
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

 
void displayAllocationMax() 
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

 
void displayNeed() 
{
    calculateNeed();  
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < num_processes; i++)
		 {
        for (int j = 0; j < num_resources; j++) 
				{
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

 
void displayAvailable() {
    printf("\nAvailable Resources:\n");
    for (int i = 0; i < num_resources; i++)
		 {
        printf("%d ", available[i]);
    }
    printf("\n");
}

int main() 
{
    int choice;

    while (1) 
		{
        printf("1. Accept Allocation and Max\n");
        printf("2. Accept Available Resources\n");
        printf("3. Display Allocation and Max\n");
        printf("4. Calculate & Display Need Matrix\n");
        printf("5. Display Available Resources\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
				{
            case 1:
                acceptMatrices();
                break;
            case 2:
                acceptAvailable();
                break;
            case 3:
                displayAllocationMax();
                break;
            case 4:
                displayNeed();
                break;
            case 5:
                displayAvailable();
                break;
            case 6:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
