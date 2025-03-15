#ifndef T_TASK_H
#define T_TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct task_t {
    int id;
    char description[100];
    int priority;
    int execution_time;
    struct task_t *next;
} task_t;



#endif