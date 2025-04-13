#include <omp.h>
#include <stdio.h>

#define N 1000

double f(int x);

int main()
{
    double A[N];

    double s = 0.0;

    #pragma omp parallel for
    for(int i = 0; i <N; i++)
    {
        int n = 9 + 2 * i;
        A[i] = f(n);
    }

    #pragma omp parallel for reduction(+:s)
    for(int i = 0; i < N; i++)
    {
        s += A[i];
    }

    printf("Soma final:%f\n",s);

    return (0);
}

double f(int x)
{
    return (x * x);
}
