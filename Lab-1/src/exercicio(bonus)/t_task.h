#ifndef T_TASK_H
#define T_TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRIORITY 5

typedef struct task_t {
    char id[50]; 
    int priority; 
    time_t created_at; 
    struct task_t *next; 
} task_t;

// Funções
task_t* createTask(const char *id, int priority);
void insertTask(task_t **head, const char *id, int priority);
void removeTask(task_t **head, const char *id);
void printTasksByPriority(task_t *head, int min_priority);
void freeList(task_t *head);

#endif