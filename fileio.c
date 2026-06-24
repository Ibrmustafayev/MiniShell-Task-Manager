#include "task.h"
#include <stdio.h>
#include <stdlib.h>

void load(Node **tasks, char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No saved tasks found. Starting fresh!\n");
        return;
    }

    Node *current = NULL;
    int count = 0;
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        fclose(fp);
        return;
    }

    while (fscanf(fp, " %d,%99[^,],%9[^,],%d", &newNode -> task.id, newNode -> task.title, newNode -> task.priority, &newNode -> task.done) == 4) {
        newNode -> next = NULL;
        if (*tasks == NULL) {
            *tasks = newNode;
        } else {
            current -> next = newNode;
        }
        current = newNode;
        count++;
        newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Memory allocation failed!");
            break;
        }
    }

    free(newNode);
    fclose(fp);
    printf("Loaded %d tasks from %s!\n", count, filename);
}

void save(Node **tasks, char *filename) {
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Not able to open %s!\n\n", filename);
        return;
    }

    if (*tasks == NULL) {
        return;
    }
    int count = 0;
    Node *current = *tasks;
    while (current != NULL) {
        fprintf(fp, "%d,%s,%s,%d\n", current -> task.id, current -> task.title, current -> task.priority, current -> task.done);
        current = current -> next;
        count++;
    }

    fclose(fp);
    printf("Saved %d tasks to %s!\n\n", count, filename);
}

void freeList(Node *tasks) {
    if (tasks == NULL) {
        return;
    }

    Node *current = tasks;
    while (current != NULL) {
        Node *temp = current;
        current = current -> next;
        free(temp);
    }
}
