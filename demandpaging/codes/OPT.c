#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

int find_next(int page_ref[], int current_pos, int num_pages, int page)
{
    for (int i = current_pos + 1; i < num_pages; i++)
    {
        if (page_ref[i] == page)
        {
            return i;
        }
    }
    return -1;
}

void OPT(int page_ref[], int num_pages, int n)
{
    int frames[MAX_FRAMES];
    int page_faults = 0;

    for (int i = 0; i < n; i++)
    {
        frames[i] = -1;
    }

    printf("\nOPT Page Replacement Algorithm:\n");

    for (int i = 0; i < num_pages; i++)
    {
        int page = page_ref[i];
        int found = 0;

        for (int j = 0; j < n; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
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
                int farthest = -1, replace_index = -1;
                for (int j = 0; j < n; j++)
                {
                    int next_use = find_next(page_ref, i, num_pages, frames[j]);
                    if (next_use == -1)
                    {
                        replace_index = j;
                        break;
                    }
                    else if (next_use > farthest)
                    {
                        farthest = next_use;
                        replace_index = j;
                    }
                }
                frames[replace_index] = page;
            }
            else
            {
                frames[free_slot] = page;
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
    printf("Total Page Faults (OPT): %d\n", page_faults);
}

int main()
{
    int page_ref[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int num_pages = sizeof(page_ref) / sizeof(page_ref[0]);
    int n;

    printf("Enter the number of memory frames: ");
    scanf("%d", &n);

    OPT(page_ref, num_pages, n);

    return 0;
}
