#include <stdio.h>
#include <string.h>
#include "task.h"

int main() {
    Node *tasks = NULL;
    char filename[]= "tasks.txt";
    char command[150];

    printf("MiniShell Task Manager v1.0\n");
    load(&tasks, filename);

    while (1) {
        int i = 0;
        printf("> ");
        fgets(command, 150, stdin);

        if (strlen(command) < 2) {
            i = converter(command, &tasks, filename);
        } else {
            if (command[strlen(command) - 2] == ' ') {command[strlen(command) - 2] = '\0';}
            else {command[strcspn(command, "\n")] = '\0';}
            i = converter(command, &tasks, filename);
        }

        if (i == 1) {break;}
    }

    return 0;
}
