#ifndef TASK_H
#define TASK_H

typedef struct {
    int id;
    char title[100];
    char priority[10]; //low, medium, high
    int done; // 1 or 0
} Task;

typedef struct Node{
    Task task;
    struct Node *next;
} Node;

//task.c
Node* createNode(int id, char *args);
void modifyId(Node *tasks);
void add(Node **tasks, char *args);
void list(Node *tasks);
void done(Node *tasks, int id);
void delete(Node **tasks, int id);
void search(Node *tasks, char *args);
void stats(Node *tasks);

//fileio.c
void load(Node **tasks, char *filename);
void save(Node **tasks, char *filename);
void freeList(Node *tasks);

//command.c
int converter(char command[], Node **tasks, char *filename);
void help();

#endif
