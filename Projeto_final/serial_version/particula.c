#include "particle.h"
#include <math.h>

unsigned int seed;

void init_r4uni(int input_seed)
{
    seed = input_seed + 987654321;
}
double rnd_uniform01()
{
    int seed_in = seed;
    seed ˆ= (seed << 13);
    seed ˆ= (seed >> 17);
    seed ˆ= (seed << 5);
    return 0.5 + 0.2328306e-09 * (seed_in + (int) seed);
}
double rnd_normal01()
{
    double u1, u2, z, result;
    double pi = acos(-1.0);

    do {
        u1 = rnd_uniform01();
        u2 = rnd_uniform01();
        z = sqrt(-2 * log(u1)) * cos(2 * pi * u2);
        result = 0.5 + 0.15 * z;
    } while (result < 0 || result >= 1);
    return result;
}

void init_particles(long seed, double side, long ncside, long long n_part, particle_t *par) {
    double (*rnd01)() = rnd_uniform01;
    long long i;
    if (seed < 0) {
        rnd01 = rnd_normal01;
        seed = -seed;
    }
    init_r4uni(seed);
    for (i = 0; i < n_part; i++) {
        par[i].x = rnd01() * side;
        par[i].y = rnd01() * side;
        par[i].vx = (rnd01() - 0.5) * side / ncside / 5.0;
        par[i].vy = (rnd01() - 0.5) * side / ncside / 5.0;
        par[i].m = rnd01() * 0.01 * (ncside * ncside) / n_part / G * EPSILON2;
    }
}

//calcula o centro de massa de cada celula
void cal_cell_centers(cell_t *cells, particle_t *particles, long long n_part, long ncside, double cell_size)
{
    //inicializa com zero os dados das celulas
    for(long i = 0; i < ncside * ncside; i++)
    {
        cells[i].cm_x = 0.0;
        cells[i].cm_y = 0.0;
        cells[i].total_mass = 0.0;
    } 

    //Calcula o centro de massa de cada celula
    for(long long i = 0; i < n_part; i++)
    {
        long cell_x = (long)(particles[i].x / cell_size);
        long cell_y = (long)(particles[i].x / cell_size);
        long cell_idx = cell_y * ncside + cell_x;

        cells[cell_idx].cm_x += particles[i].x * particles[i].m;
    }
}