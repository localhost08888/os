
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void maketokens(char *s, char *tok[]) {
    int i = 0;
    char *p = strtok(s, " \n");
    while (p != NULL && i < 9) { // Limit to 9 tokens
        tok[i++] = p;
        p = strtok(NULL, " \n");
    }
    tok[i] = NULL;
}

void search(char mode, const char *filename, const char *pattern) {
    if (filename == NULL || pattern == NULL) {
        printf("Usage: search <mode> <filename> <pattern>\n");
        return;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found.\n");
        return;
    }

    char line[1024];
    int line_num = 0, count = 0;
    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        if (strstr(line, pattern)) {
            if (mode == 'f') {
                printf("First occurrence at line %d: %s", line_num, line);
                fclose(fp);
                return;
            } else if (mode == 'a') {
                printf("Occurrence at line %d: %s", line_num, line);
            } else if (mode == 'c') {
                count++;
            }
        }
    }
    if (mode == 'c') {
        printf("Pattern found %d times.\n", count);
    } else if (mode == 'f') {
        printf("Pattern not found.\n");
    }
    fclose(fp);
}

void typeline(char mode, int n, const char *filename) {
    if (filename == NULL || n < 0) {
        printf("Usage: typeline <mode> <n> <filename>\n");
        return;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found.\n");
        return;
    }

    char lines[1024][1024];
    int line_count = 0;
    while (fgets(lines[line_count], sizeof(lines[line_count]), fp)) {
        line_count++;
    }
    fclose(fp);

    if (mode == 'a') {
        for (int i = 0; i < line_count; i++) {
            printf("%s", lines[i]);
        }
    } else if (mode == 'n') {
        for (int i = 0; i < n && i < line_count; i++) {
            printf("%s", lines[i]);
        }
    } else if (mode == '-') {
        for (int i = (line_count - n < 0 ? 0 : line_count - n); i < line_count; i++) {
            printf("%s", lines[i]);
        }
    }
}

void list(char mode, const char *dirname) {
    if (dirname == NULL) {
        printf("Usage: list <mode> <directory>\n");
        return;
    }

    DIR *dir = opendir(dirname);
    if (!dir) {
        printf("Directory %s not found.\n", dirname);
        return;
    }

    struct dirent *entry;
    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
        count++;
        if (mode == 'n') {
            printf("%s\n", entry->d_name);
        } else if (mode == 'i') {
            printf("Filename: %s, Inode: %ld\n", entry->d_name, entry->d_ino);
        }
    }
    if (mode == 'c') {
        printf("Total entries: %d\n", count);
    }
    closedir(dir);
}

int main() {
    char buff[80], *args[10];
    while (1) {
        printf("myshell$ ");
        fflush(stdout);
        if (!fgets(buff, sizeof(buff), stdin)) {
            break;
        }
        maketokens(buff, args);

        if (args[0] == NULL) {
            continue;
        }

        if (strcmp(args[0], "search") == 0) {
            if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
                printf("Usage: search <mode> <filename> <pattern>\n");
            } else {
                search(args[1][0], args[2], args[3]);
            }
        } else if (strcmp(args[0], "typeline") == 0) {
            if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
                printf("Usage: typeline <mode> <n> <filename>\n");
            } else {
                typeline(args[1][0], atoi(args[2]), args[3]);
            }
        } else if (strcmp(args[0], "list") == 0) {
            if (args[1] == NULL || args[2] == NULL) {
                printf("Usage: list <mode> <directory>\n");
            } else {
                list(args[1][0], args[2]);
            }
        } else {
            pid_t pid = fork();
            if (pid < 0) {
                perror("Fork failed");
            } else if (pid > 0) {
                wait(NULL);
            } else {
                if (execvp(args[0], args) == -1) {
                    printf("Bad command.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    return 0;
}
