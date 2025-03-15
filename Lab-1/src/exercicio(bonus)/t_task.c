#include "t_task.h"
void addTask(task_t task_list)
{
    
}

task_t * createTask(int id, char *description, int priority, int time_execution)
{
    task_t *new_task = (task_t *)malloc(sizeof(task_t));
    
    if(!new_task)
    {
        printf("Erro de memoria!\n");
        exit(1);
    }
    new_task->id = id;
    strcpy(new_task->description, description);
    new_task->priority = priority;
    new_task->execution_time = time_execution;
    new_task->next = NULL;

    return new_task;
}

void insertTaskWithPriority(task_t** head,int id, char *description, int priority, int time_execution)
{
    task_t *new_task = createTask(id, description, priority, time_execution);

    if(*head == NULL || (*head)->priority < priority)
    {
        new_task->next = *head;
        *head = new_task;
    }else{
        task_t* current = *head;
        while(current->next != NULL && current->next->priority >= priority)
        {
            current = current->next;
        }
        new_task->next = current->next;
        current->next = new_task;
    }
}

int removeHighestPriority(task_t** head)
{
    if(*head == NULL)
    {
        printf("Lista vazia!\n");
        return (-1);
    }

    task_t *temp = *head;
    int id = temp->id;
    *head = (*head)->next;
    free(temp);
    
    return (id);
}