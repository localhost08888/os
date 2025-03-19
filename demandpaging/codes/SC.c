#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 16

void SecondChance(int page_ref[], int num_pages, int n)
{
    int frames[MAX_FRAMES] = {-1, -1, -1};
    int reference_bit[MAX_FRAMES] = {0};
    int page_faults = 0;
    int i, j;
    int pointer = 0;

    printf("\nSecond Chance Page Replacement Algorithm:\n");

    for (i = 0; i < num_pages; i++)
    {
        int page = page_ref[i];
        int found = 0;

        for (j = 0; j < n; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                reference_bit[j] = 1;
                break;
            }
        }

        if (!found)
        {
            while (1)
            {
                if (frames[pointer] == -1)
                {
                    frames[pointer] = page;
                    reference_bit[pointer] = 1;
                    break;
                }
                else if (reference_bit[pointer] == 0)
                {
                    frames[pointer] = page;
                    reference_bit[pointer] = 1;
                    break;
                }
                else
                {
                    reference_bit[pointer] = 0;
                }
                pointer = (pointer + 1) % n;
            }
            page_faults++;
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
    printf("Total Page Faults (Second Chance): %d\n", page_faults);
}

int main()
{
    int page_ref[MAX_PAGES] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 21, 34, 56, 78, 89, 3, 42};
    int num_pages = 16;
    int n;

    printf("Enter the number of memory frames: ");
    scanf("%d", &n);

    SecondChance(page_ref, num_pages, n);

    return 0;
}