#include <stdio.h>
#include <omp.h>

int main()
{
    int i;
    
    #pragma omp parallel private(i) num_threads(2)
    for(i = 0; i < 4; i++)
        printf("%d ",i);
    
    printf("\n\n");

    #pragma omp parallel for private(i) num_threads(2)
    for(i = 0; i < 4; i++)
        printf("%d ",i);
    

    return (0);
}

