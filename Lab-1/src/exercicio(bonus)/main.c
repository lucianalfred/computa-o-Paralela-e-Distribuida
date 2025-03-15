#include "t_task.h"
#include <string.h>

#define MAX_INPUT_SIZE 100
#define MAX_ID_SIZE 50

int main() {
    task_t *tasks[MAX_PRIORITY + 1] = {NULL}; 
    char input[MAX_INPUT_SIZE];
    char command[20], id[MAX_ID_SIZE];
    int priority;

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; 
        }

        
        input[strcspn(input, "\n")] = '\0';

        
        if (sscanf(input, "%s", command) != 1) {
            continue; 
        }

        if (strcmp(command, "new") == 0) {
            
            if (sscanf(input, "%*s %d %s", &priority, id) != 2) {
                continue; 
            }
            if (priority < 0 || priority > MAX_PRIORITY) {
                continue; 
            }
            insertTask(&tasks[priority], id, priority);
        } else if (strcmp(command, "list") == 0) {
          
            if (sscanf(input, "%*s %d", &priority) != 1) {
                continue; 
            }
            if (priority < 0 || priority > MAX_PRIORITY) {
                continue; 
            }
            for (int i = MAX_PRIORITY; i >= priority; i--) {
                printTasksByPriority(tasks[i], priority);
            }
        } else if (strcmp(command, "complete") == 0) {
            
            if (sscanf(input, "%*s %s", id) != 1) {
                continue;             }
            int found = 0;
            for (int i = 0; i <= MAX_PRIORITY; i++) {
                task_t *prev = NULL;
                task_t *current = tasks[i];
                while (current != NULL) {
                    if (strcmp(current->id, id) == 0) {
                        if (prev == NULL) {
                            tasks[i] = current->next;
                        } else {
                            prev->next = current->next;
                        }
                        free(current);
                        found = 1;
                        break;
                    }
                    prev = current;
                    current = current->next;
                }
                if (found) break;
            }
            if (!found) {
                fprintf(stderr, "TAREFA INEXISTENTE\n");
            }
        } else if (strcmp(command, "exit") == 0) {
           
            break;
        }
    }

   
    for (int i = 0; i <= MAX_PRIORITY; i++) {
        freeList(tasks[i]);
    }

    return 0;
}