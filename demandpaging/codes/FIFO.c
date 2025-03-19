#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

int is_page_in_memory(int page, int frames[], int num_frames)
{
    for (int i = 0; i < num_frames; i++)
    {
        if (frames[i] == page)
        {
            return 1;
        }
    }
    return 0;
}

void fifo_page_replacement(int reference_string[], int num_references, int num_frames)
{
    int frames[num_frames];
    int page_faults = 0;
    int next_frame = 0;

    for (int i = 0; i < num_frames; i++)
    {
        frames[i] = -1;
    }

    printf("\nFIFO Page Replacement Algorithm:\n");
    for (int i = 0; i < num_references; i++)
    {
        int page = reference_string[i];
        printf("Accessing page %d: ", page);

        if (!is_page_in_memory(page, frames, num_frames))
        {
            frames[next_frame] = page;
            next_frame = (next_frame + 1) % num_frames;
            page_faults++;
            printf("Page Fault!\n");
        }
        else
        {
            printf("No Page Fault.\n");
        }

        printf("Memory Frames: ");
        for (int j = 0; j < num_frames; j++)
        {
            if (frames[j] != -1)
            {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", page_faults);
}

int main()
{
    int reference_string[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int num_references = sizeof(reference_string) / sizeof(reference_string[0]);

    int num_frames;
    printf("Enter the number of memory frames: ");
    scanf("%d", &num_frames);

    fifo_page_replacement(reference_string, num_references, num_frames);

    return 0;
}
