#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

void LFU(int page_ref[], int num_pages, int n)
{
    int frames[MAX_FRAMES], frequency[MAX_FRAMES] = {0};
    int page_faults = 0;

    for (int i = 0; i < n; i++)
    {
        frames[i] = -1;
    }

    printf("\nLFU Page Replacement Algorithm:\n");

    for (int i = 0; i < num_pages; i++)
    {
        int page = page_ref[i];
        int found = 0;

        for (int j = 0; j < n; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                frequency[j]++;
                break;
            }
        }

        if (!found)
        {
            int free_slot = -1;
            for (int j = 0; j < n; j++)
            {
                if (frames[j] == -1)
                {
                    free_slot = j;
                    break;
                }
            }

            if (free_slot == -1)
            {
                int min_freq = 9999, replace_index = -1;
                for (int j = 0; j < n; j++)
                {
                    if (frequency[j] < min_freq)
                    {
                        min_freq = frequency[j];
                        replace_index = j;
                    }
                }
                frames[replace_index] = page;
                frequency[replace_index] = 1;
            }
            else
            {
                frames[free_slot] = page;
                frequency[free_slot] = 1;
            }

            page_faults++;
            printf("Accessing page %d: Page Fault!\n", page);
        }

        printf("Memory Frames: ");
        for (int j = 0; j < n; j++)
        {
            if (frames[j] != -1)
            {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }
    printf("Total Page Faults (LFU): %d\n", page_faults);
}

int main()
{
    int page_ref[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int num_pages = sizeof(page_ref) / sizeof(page_ref[0]);
    int n;

    printf("Enter the number of memory frames: ");
    scanf("%d", &n);

    LFU(page_ref, num_pages, n);

    return 0;
}
