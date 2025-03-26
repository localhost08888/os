#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

void maketokens(char *s, char *tok[]) 
{
    int i = 0;
    char *p = strtok(s, " \n");
    while (p != NULL)  
    {
        tok[i++] = p;
        p = strtok(NULL, " \n");
    }
    tok[i] = NULL;
}

void search(char mode, const char *filename, const char *pattern)  
{
    FILE *fp = fopen(filename, "r");
    char line[500];
    int linenum = 0, count = 0;

    while (fgets(line, sizeof(line), fp)) 
    {
        linenum++;
        if (strstr(line, pattern))  
        {
            if (mode == 'f')  
            {
                printf("First occurrence at line %d: %s", linenum, line);
                break;
            }
            else if (mode == 'a')  
            {
                printf("Occurrence at line %d: %s", linenum, line);
            }
            else if (mode == 'c') 
            {
                count++;
            }
        }
    }

    if (mode == 'c')  
        printf("Pattern found %d times.\n", count);
    else if (mode == 'f' && count == 0)  
        printf("Pattern not found.\n");

    fclose(fp);
}

void typeline(char mode, int n, const char *filename)  
{
    FILE *fp = fopen(filename, "r");
    char line[500];
    int line_count = 0;

    if (mode == '-')  
    {
        while (fgets(line, sizeof(line), fp))
            line_count++;
        rewind(fp);
    }

    int printed = 0;
    while (fgets(line, sizeof(line), fp))  
    {
        if (mode == 'a' || (mode == 'n' && printed < n) ||  (mode == '-' && line_count - printed <= n))
        {  
            printf("%s", line);
        }
        printed++;
    }

    fclose(fp);
}

void list(char mode, const char *dirname)  
{
    DIR *dir = opendir(dirname);
    if (!dir)  
    {
        printf("Directory not found: %s\n", dirname);
        return;
    }

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL)  
    {
        if (mode == 'c')
            count++;
        else if (mode == 'n')
            printf("%s\n", entry->d_name);
        else if (mode == 'i')
            printf("%s (Inode: %ld)\n", entry->d_name, entry->d_ino);
    }

    if (mode == 'c')
        printf("Total entries: %d\n", count);

    closedir(dir);
}

void count(const char *filename, char option) 
{
    int file = open(filename, O_RDONLY);
    int chars = 0, words = 0, lines = 0;
    char c, prev = ' ';

    while (read(file, &c, 1) > 0)  
    {
        chars++;
        if (c == ' ' || c == '\n')
        {
            if (prev != ' ' && prev != '\n')
                words++;
        }
        if (c == '\n')
            lines++;
        prev = c;
    }
    close(file);

    if (option == 'c')  
        printf("Characters: %d\n", chars);
    else if (option == 'w')  
        printf("Words: %d\n", words);
    else if (option == 'l')  
        printf("Lines: %d\n", lines);
    else printf("Invalid option! Use 'c', 'w', or 'l'.\n");
}

int main()  
{
    char buff[80], *args[10];

    while (1)    
    {
        printf("myshell$ ");
        fflush(stdout);

        if (!fgets(buff, sizeof(buff), stdin))  
            break;

        maketokens(buff, args);
        if (!args[0])     
            continue;    

        if (strcmp(args[0], "search") == 0)
            search(args[1][0], args[2], args[3]);  
        else if (strcmp(args[0], "typeline") == 0)
            typeline(args[1][0], atoi(args[2]), args[3]);        
        else if (strcmp(args[0], "list") == 0)
            list(args[1][0], args[2]);
        else if (strcmp(args[0], "count") == 0)
            count(args[1], args[2][0]);  
        else 
            printf("Unknown command: %s\n", args[0]);
    }

    return 0;
}
