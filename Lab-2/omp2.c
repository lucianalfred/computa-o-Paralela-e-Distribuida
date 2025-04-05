/*
	Name: Lab#2
	Copyright: 2021-22
	Author: Prof. Joao Costa
	Date: 06/04/22 17:24
	Description: 
		Parallelizing an inner loop with dependences
	
			for (iter=0; iter<numiter; iter++) {
				for (i=0; i<size-1; i++) {
					V[i] = f( V[i], V[i+1] );
				}
			}
*/

#include<stdio.h>
#include<stdlib.h>

#define TOTALSIZE 1000
#define NUMITER 200

/*
* DUMMY FUNCTION
*/
#define f(x,y)	((x+y)/2.0)


/* MAIN: PROCESS PARAMETERS */
int main(int argc, char *argv[]) {

  /* VARIABLES */
  int i, iter;

  /* DECLARE VECTOR AND AUX DATA STRUCTURES */
  double *V = (double *) malloc(TOTALSIZE * sizeof(double));

  /* 1. INITIALIZE VECTOR */
  for(i = 0; i < TOTALSIZE; i++) {
    V[i]= 0.0 + i;
  }

  double *V1 = (double *) malloc(TOTALSIZE * sizeof(double));
double *V2 = (double *) malloc(TOTALSIZE * sizeof(double));

// inicializar V1
for(i = 0; i < TOTALSIZE; i++) {
    V1[i] = 0.0 + i;
}

double *src = V1;
double *dest = V2;

for(iter = 0; iter < NUMITER; iter++) {

    #pragma omp parallel for
    for(i = 0; i < TOTALSIZE - 1; i++) {
        dest[i] = f(src[i], src[i+1]);
    }

    // copiar último valor (não processado no loop)
    dest[TOTALSIZE - 1] = src[TOTALSIZE - 1];

    // troca ponteiros
    double *tmp = src;
    src = dest;
    dest = tmp;
}



  /* 3. OUTPUT FINAL VALUES */
  printf("Output:\n"); 
  for(i = 0; i < TOTALSIZE; i++) {
    printf("%4d %f\n", i, V[i]);
  }

}