#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
 
struct DirectoryEntry 
{
    char filename[20];
    int start_block;
    int num_blocks;
};

 
int *bit_vector;   
struct DirectoryEntry directory[MAX_FILES];
int num_blocks, num_files = 0;


void show_bit_vector()
 {
    
    for (int i = 0; i < num_blocks; i++)
     {
        printf("%d ", bit_vector[i]);
    }
    printf("\n");
}

 
void create_new_file()
 {
    char filename[20];
    int num_blocks_to_allocate, start_block = -1;

    printf("\nEnter file name: ");
    scanf("%s", filename);
    printf("Enter number of blocks to allocate: ");
    scanf("%d", &num_blocks_to_allocate);

    if (num_blocks_to_allocate > num_blocks)
     {
        printf("Error: Requested blocks exceed total available blocks.\n");
        return;
    }

    
    for (int i = 0; i <= num_blocks - num_blocks_to_allocate; i++)
     {
        int found = 1;
        for (int j = 0; j < num_blocks_to_allocate; j++) 
        {
            if (bit_vector[i + j] == 1) 
            {
                found = 0;
                break;
            }
        }
        if (found) 
        {
            start_block = i;
            break;
        }
    }

    if (start_block == -1) 
    {
        printf("Error: Not enough contiguous free blocks available.\n");
        return;
    }

 
    for (int i = 0; i < num_blocks_to_allocate; i++)
     {
        bit_vector[start_block + i] = 1;
    }
 
    strcpy(directory[num_files].filename, filename);
    directory[num_files].start_block = start_block;
    directory[num_files].num_blocks = num_blocks_to_allocate;
    num_files++;

    printf("File '%s' created at block %d with %d blocks.\n", filename, start_block, num_blocks_to_allocate);
}

 
void show_directory() 
{
    if (num_files == 0)
     {
        printf("\nDirectory is empty.\n");
        return;
    }
 
    for (int i = 0; i < num_files; i++)
     {
        printf("File: %s | Start Block: %d | Blocks: %d\n", 
                directory[i].filename, directory[i].start_block, directory[i].num_blocks);
    }
}

 
void delete_file()
 {
    char filename[20];
    printf("\nEnter file name to delete: ");
    scanf("%s", filename);

    int file_index = -1;
    for (int i = 0; i < num_files; i++)
     {
        if (strcmp(directory[i].filename, filename) == 0) 
        {
            file_index = i;
            break;
        }
    }

    if (file_index == -1) 
    {
        printf("Error: File not found.\n");
        return;
    }
 
    for (int i = 0; i < directory[file_index].num_blocks; i++)
     {
        bit_vector[directory[file_index].start_block + i] = 0;
    }
 
    for (int i = file_index; i < num_files - 1; i++) 
    {
        directory[i] = directory[i + 1];
    }
    num_files--;

    printf("File '%s' deleted successfully.\n", filename);
}

 
int main() 
{
    int option;
 
    printf("Enter total number of blocks on the disk: ");
    scanf("%d", &num_blocks);

    bit_vector = (int *)malloc(num_blocks * sizeof(int));
    if (!bit_vector)
     {
        printf("Memory allocation failed!\n");
        return 1;
    }
    memset(bit_vector, 0, num_blocks * sizeof(int));  
 
    do  
   {
 
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) 
        {
            case 1: show_bit_vector();
             break;
            case 2: create_new_file(); 
            break;
            case 3: show_directory();
             break;
            case 4: delete_file();
             break;
            case 5: printf("Exiting...\n");
             break;
            default: printf("Invalid option. Please try again.\n");
        }
    } 
    while (option != 5);

    
    free(bit_vector);
    return 0;
}
