#include "t_task.h"

task_t* createTask(const char *id, int priority) {
    task_t *new_task = (task_t *)malloc(sizeof(task_t));
    if (!new_task) {
        fprintf(stderr, "Erro de memória!\n");
        exit(1);
    }

    strncpy(new_task->id, id, sizeof(new_task->id) - 1);
    new_task->id[(sizeof(new_task->id) - 1)] = '\0'; 
    new_task->priority = priority;
    new_task->created_at = time(NULL); 
    new_task->next = NULL;

    return new_task;
}

void insertTask(task_t **head, const char *id, int priority) {
    task_t *new_task = createTask(id, priority);

    if (*head == NULL || (*head)->priority < priority || 
        ((*head)->priority == priority && (*head)->created_at > new_task->created_at)) {
        new_task->next = *head;
        *head = new_task;
    } else {
        task_t *current = *head;
        while (current->next != NULL && 
               (current->next->priority > priority || 
                (current->next->priority == priority && current->next->created_at < new_task->created_at))) {
            current = current->next;
        }
        new_task->next = current->next;
        current->next = new_task;
    }
}

void removeTask(task_t **head, const char *id) {
    if (*head == NULL) {
        fprintf(stderr, "TAREFA INEXISTENTE\n");
        return;
    }

    task_t *temp = *head;
    task_t *prev = NULL;

    if (strcmp(temp->id, id) == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    // Procura a tarefa na lista
    while (temp != NULL && strcmp(temp->id, id) != 0) {
        prev = temp;
        temp = temp->next;
    }

    
    if (temp == NULL) {
        fprintf(stderr, "TAREFA INEXISTENTE\n");
        return;
    }

    prev->next = temp->next;
    *head = prev;
    free(temp);
}


void printTasksByPriority(task_t *head, int min_priority) {
    task_t *current = head;
    int count = 0;

    printf("Tarefas com prioridade >= %d:\n", min_priority);
    while (current != NULL) {
        if (current->priority >= min_priority) {
            printf("ID: %s | Prioridade: %d | Criada em: %s", current->id, current->priority, ctime(&current->created_at));
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("Nenhuma tarefa encontrada.\n");
    }
}


void freeList(task_t *head) {
    task_t *current = head;
    task_t *next_task;
    while (current != NULL) {
        next_task = current->next;
        free(current);
        current = next_task;
    }
}