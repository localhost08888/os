#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 16

void MRU(int page_ref[], int num_pages, int n) 
{
    int frames[MAX_FRAMES] = {-1, -1, -1};
    int last_used[MAX_FRAMES] = {0};
    int page_faults = 0;
    int i, j;

    printf("\nMRU Page Replacement Algorithm:\n");

    for (i = 0; i < num_pages; i++)
     {
        int page = page_ref[i];
        int found = 0;

        for (j = 0; j < n; j++) 
        {
            if (frames[j] == page)
             {
                found = 1;
                break;
            }
        }

        if (!found)
         {
            int most_recent = -1;
            int replace_index = -1;

            for (j = 0; j < n; j++)
             {
                if (last_used[j] > most_recent)
                 {
                    most_recent = last_used[j];
                    replace_index = j;
                }
            }

            frames[replace_index] = page;
            page_faults++;

            last_used[replace_index] = i;

            printf("Accessing page %d: Page Fault!\n", page);
            printf("Memory Frames: ");
            for (j = 0; j < n; j++) 
            {
                if (frames[j] != -1)
                 {
                    printf("%d ", frames[j]);
                }
            }
            printf("\n");
        }
    }
    printf("Total Page Faults (MRU): %d\n", page_faults);
}

int main()
 {
    int page_ref[MAX_PAGES] = {1,3,5,7,9,2,4,6,8,21,34,56,78,89,3,42};
    int num_pages = 16;
    int n;

    printf("Enter the number of memory frames: ");
    scanf("%d", &n);

    MRU(page_ref, num_pages, n);

    return 0;
}