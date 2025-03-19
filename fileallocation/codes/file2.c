#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
 
struct Block 
{
    int block_num;
    struct Block *next;
};
 
struct DirectoryEntry 
{
    char filename[20];
    struct Block *start_block;
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
 
int find_free_block()
 {
    for (int i = 0; i < num_blocks; i++)
     {
        if (bit_vector[i] == 0) 
        {
            return i;
        }
    }
    return -1;
}

 
void create_new_file() 
{
    char filename[20];
    int num_blocks_to_allocate;

    printf("\nEnter file name: ");
    scanf("%s", filename);
    printf("Enter number of blocks to allocate: ");
    scanf("%d", &num_blocks_to_allocate);

    if (num_blocks_to_allocate > num_blocks)
     {
        printf("Error: Not enough blocks available.\n");
        return;
    }
 
    struct Block *head = NULL, *tail = NULL;
    for (int i = 0; i < num_blocks_to_allocate; i++)
     {
        int free_block = find_free_block();
        if (free_block == -1) 
        {
            printf("Error: No more free blocks available.\n");
            return;
        }
        bit_vector[free_block] = 1;

        struct Block *new_block = (struct Block *)malloc(sizeof(struct Block));
        new_block->block_num = free_block;
        new_block->next = NULL;

        if (head == NULL) 
        {
            head = new_block;
            tail = new_block;
        } 
        else
         {
            tail->next = new_block;
            tail = new_block;
        }
    }

 
    strcpy(directory[num_files].filename, filename);
    directory[num_files].start_block = head;
    num_files++;

    printf("File '%s' created with %d blocks.\n", filename, num_blocks_to_allocate);
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
        printf("File: %s | Blocks: ", directory[i].filename);
        struct Block *temp = directory[i].start_block;
        while (temp)
         {
            printf("%d -> ", temp->block_num);
            temp = temp->next;
        }
        printf("NULL\n");
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

 
    struct Block *temp = directory[file_index].start_block;
    while (temp) 
    {
        bit_vector[temp->block_num] = 0;
        struct Block *next_block = temp->next;
        free(temp);
        temp = next_block;
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

        switch (option) {
            case 1: show_bit_vector(); break;
            case 2: create_new_file(); break;
            case 3: show_directory(); break;
            case 4: delete_file(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid option. Please try again.\n");
        }
    } 
    while (option != 5);
     free(bit_vector);
    return 0;
}
