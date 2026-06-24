#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Node* createNode(int id, char *args) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    char *lastSpace, *title, *priority;
    char lastWord[10];
    int i;

    lastSpace = strrchr(args, ' ');
    if (lastSpace == NULL) {
        free(newNode);
        return NULL;
    }

    char *raw = lastSpace + 1;
    for (i = 0; raw[i] && i < 9; i++) lastWord[i] = tolower(raw[i]);
    lastWord[i] = '\0';

    if (strcmp(lastWord, "low") == 0 || strcmp(lastWord, "medium") == 0 || strcmp(lastWord, "high") == 0) {
        *lastSpace = '\0';
        title = args;
        priority = raw;
    } else {
        title = args;
        priority = "medium";
    }

    newNode->task.id = id;
    strcpy(newNode->task.title, title);
    strcpy(newNode->task.priority, priority);
    newNode->task.done = 0;
    newNode->next = NULL;

    return newNode;
}

void modifyId(Node *tasks) {
    if (tasks == NULL) {
        return;
    }

    int id = 0;
    Node *current = tasks;
    while (current != NULL) {
        current -> task.id = id;
        current = current -> next;
        id++;
    }
}

void add(Node **tasks, char *args) {
    int id = 0;

    if (*tasks == NULL) {
        *tasks = createNode(id, args);
        printf("Task added! ID: %d\n\n", id + 1);
        return;
    }

    Node *current = *tasks;
    while (current -> next != NULL) {current = current -> next; id++;}
    current -> next = createNode(id + 1, args);

    printf("Task added! ID: %d\n\n", id + 2);
}

void list(Node *tasks) {
    if (tasks == NULL) {
        printf("None!");
        return;
    }

    Node *current = tasks;
    while (current != NULL) {
        printf((current -> task.done == 1) ? "[+]" : "[ ]");
        printf(" %d. %s\t[%s]\n", current -> task.id + 1, current -> task.title, current -> task.priority);
        current = current -> next;
    }
    printf("\n");
}

void done(Node *tasks, int id) {
    if (tasks == NULL) {
        printf("Add task first!\n\n");
        return;
    }

    Node *current = tasks;
    while (current != NULL) {
        if (id == current -> task.id) {
            current -> task.done = 1;
            printf("Task %d marked as complete!\n\n", id + 1);
            return;
        }
        current = current -> next;
    }
    printf("Invalid index!\n\n");
}

void delete(Node **tasks, int id) { ///
    if (*tasks == NULL) {
        printf("Add task first!\n\n");
        return;
    }

    if (id == (*tasks) -> task.id) {
        Node *temp = *tasks;
        *tasks = (*tasks) -> next;
        free(temp);
        modifyId(*tasks);
        printf("Task deleted! ID: %d\n\n", id + 1);
        return;
    }

    Node *current = *tasks;
    while (current -> next != NULL) {
        if (id == current -> next -> task.id) {
            Node *temp = current -> next;
            current -> next = temp -> next;
            free(temp);
            modifyId(*tasks);
            printf("Task deleted! ID: %d\n\n", id + 1);
            return;
        }
        current = current -> next;
    }
    printf("Invalid index!\n\n");
}

void search(Node *tasks, char *args) {
    if (tasks == NULL) {
        printf("Add task first!\n\n");
        return;
    }

    char lowerTitle[100], lowerArgs[100];
    Node *current = tasks;
    int i, k = 0;

    for (i = 0; args[i]; i++) lowerArgs[i] = tolower(args[i]);
    lowerArgs[i] = '\0';

    while (current != NULL) {
        for (i = 0; current->task.title[i]; i++) lowerTitle[i] = tolower(current->task.title[i]);
        lowerTitle[i] = '\0';

        if (strstr(lowerTitle, lowerArgs) != NULL) {
            printf("Task found!\n");
            printf((current -> task.done == 1) ? ("[+] ") : ("[ ] "));
            printf("%d. %s\t[%s]\n", current -> task.id + 1, current -> task.title, current -> task.priority);
            k++;
        }

        current = current -> next;
    }

    if (k == 0) {printf("Not found!\n\n");}
    else {printf("\n");}
}

void stats(Node *tasks) {
    if (tasks == NULL) {
        printf("Total:\t 0\nDone:\t 0\nPending: 0\nHigh:\t 0 | Medium: 0 | Low: 0\n\n");
        return;
    }

    Node *current = tasks;
    int total = 0, done = 0, high = 0, medium = 0;

    while (current != NULL) {
        total++;
        if (current -> task.done == 1) {done++;}
        if (strcmp(current -> task.priority, "high") == 0) {high++;}
        if (strcmp(current -> task.priority, "medium") == 0) {medium++;}
        current = current -> next;
    }

    printf("Total:\t %d\nDone:\t %d\nPending: %d\nHigh:\t %d | Medium: %d | Low: %d\n\n", total, done, total - done, high, medium, total - high - medium);
}
