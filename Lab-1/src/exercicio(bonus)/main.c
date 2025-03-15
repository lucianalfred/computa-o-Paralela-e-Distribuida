#include "t_task.h"
#include <string.h>

int main() {
    task_t *tasks[MAX_PRIORITY + 1] = {NULL}; // Listas para cada prioridade (0 a 5)
    char command[20], id[50];
    int priority;

    while (1) {
        printf("Comando (new/list/complete/exit): ");
        scanf("%s", command);

        if (strcmp(command, "new") == 0) {
            printf("Prioridade (0-5) e ID: ");
            scanf("%d %s", &priority, id);
            if (priority < 0 || priority > MAX_PRIORITY) {
                fprintf(stderr, "Prioridade inválida! Deve ser entre 0 e 5.\n");
                continue;
            }
            insertTask(&tasks[priority], id, priority);
            printf("Tarefa adicionada.\n");
        } else if (strcmp(command, "list") == 0) {
            printf("Prioridade mínima: ");
            scanf("%d", &priority);
            if (priority < 0 || priority > MAX_PRIORITY) {
                fprintf(stderr, "Prioridade inválida! Deve ser entre 0 e 5.\n");
                continue;
            }
            for (int i = MAX_PRIORITY; i >= priority; i--) {
                printTasksByPriority(tasks[i], priority);
            }
        } else if (strcmp(command, "complete") == 0) {
            printf("ID da tarefa: ");
            scanf("%s", id);
            for (int i = 0; i <= MAX_PRIORITY; i++) {
                removeTask(&tasks[i], id);
            }
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            fprintf(stderr, "Comando inválido!\n");
        }
    }

    // Libera a memória de todas as listas
    for (int i = 0; i <= MAX_PRIORITY; i++) {
        freeList(tasks[i]);
    }

    return 0;
}