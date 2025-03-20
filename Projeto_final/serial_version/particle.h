#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define G 6.67408e-11
#define EPSILON2 (0.005*0.005)
#define DELTAT 0.1



typedef struct {

    double x;
    double y;
    double m;
    double vx;
    double vy;
 
}particle_t;

typedef struct{
    double cm_x;
    double cm_y;
    double total_mass;
}cell_t;


void init_r4uni(int input_seed);
double rnd_uniform01();
double rnd_normal01();
void init_particles(long seed, double side, long ncside,long long n_part, particle_t *par);

#endif