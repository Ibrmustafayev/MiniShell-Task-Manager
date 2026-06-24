#include "task.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int converter(char command[], Node **tasks, char *filename) {
    if (strcmp(command, "help") == 0) {
        help();
    } else if (strcmp(command, "exit") == 0) {
        save(tasks, filename);
        freeList(*tasks);
        return 1;
    } else if (strncmp(command, "add", 3) == 0 && command[3] == ' ') {
        char *args = command + 4;
        add(tasks, args);
    } else if (strcmp(command, "list") == 0) {
        list(*tasks);
    } else if (strncmp(command, "done", 4) == 0 && command[4] == ' ') {
        char *args = command + 5;
        done(*tasks, atoi(args) - 1);
    } else if (strncmp(command, "delete", 6) == 0 && command[6] == ' ') {
        char *args = command + 7;
        delete(tasks, atoi(args) - 1);
    } else if (strncmp(command, "search", 6) == 0 && command[6] == ' ') {
        char *args = command + 7;
        search(*tasks, args);
    } else if (strcmp(command, "stats") == 0) {
        stats(*tasks);
    } else if (strcmp(command, "save") == 0) {
        save(tasks, filename);
    } else {
        printf("#Invalid command! It may be related to unproper spaces or invalid command input. Enter 'help' to show all commands.\n\n");
    }
    return 0;
}

void help() {
    printf("#Executable commands for users:\nadd <title> <priority> - adds task with auto-incremented ID");
    printf("\nlist - prints all tasks with status ([+] or [ ])");
    printf("\ndone <id> - marks task as complete");
    printf("\ndelete <id> - removes task from linked list, frees memory");
    printf("\nsearch <keyword> - finds tasks containing keyword (case-insensitive)");
    printf("\nstats - shows total, done, pending, breakdown by priority");
    printf("\nhelp - prints all commands");
    printf("\nexit - saves automatically then exits\n");
    printf("\n#Inexecutable commands for users:\nsave - saves all tasks to tasks.txt");
    printf("\nload - loads tasks from tasks.txt on startup automatically\n\n");
}
