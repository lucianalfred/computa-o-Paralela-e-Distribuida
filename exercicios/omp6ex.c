#include <stdio.h>
#include <omp.h>

int main()
{
    int i, p, x[5] = {1,1,1,1,1}, y[5] = {0,1,2,3,4};

    #pragma omp parallel private(p)
    {
        p = 5;
        #pragma omp for
        for(i = 0; i < 5; i++)
            x[i] = y[i] + p;
    }

    for(int i = 0; i < 5; i++)
    {
        printf("%d ",x[i]);
    }

    printf("\n");
    for(int i = 0; i < 5; i++)
    {
        printf("%d ",y[i]);
    }
    return (0);
}