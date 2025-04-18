#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define G 6.67408e-11
#define EPSILON2 (0.005 * 0.005)
#define DELTAT 0.1

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


typedef struct {
    double x, y;
    double vx, vy;
    double m;
    int active;
} particle_t;

static unsigned int seed;

void init_r4uni(int input_seed) {
    seed = input_seed + 987654321;
}

double rnd_uniform01() {
    int seed_in = seed;
    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 5);
    return 0.5 + 0.2328306e-09 * (seed_in + (int) seed);
}

double rnd_normal01() {
    double u1, u2, z, result;
    do {
        u1 = rnd_uniform01();
        u2 = rnd_uniform01();
        z = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
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
        par[i].active = 1;
    }
}

void compute_forces(particle_t *particles, long long n_part, double side, long ncside) {
    for (long long i = 0; i < n_part; i++) {
        if (!particles[i].active) continue;
        double fx = 0, fy = 0;
        for (long long j = 0; j < n_part; j++) {
            if (i == j || !particles[j].active) continue;
            double dx = particles[j].x - particles[i].x;
            double dy = particles[j].y - particles[i].y;
            double dist2 = dx * dx + dy * dy + EPSILON2;
            double force = G * particles[i].m * particles[j].m / dist2;
            fx += force * dx / sqrt(dist2);
            fy += force * dy / sqrt(dist2);
        }
        particles[i].vx += (fx / particles[i].m) * DELTAT;
        particles[i].vy += (fy / particles[i].m) * DELTAT;
    }
}

void update_positions(particle_t *particles, long long n_part, double side) {
    for (long long i = 0; i < n_part; i++) {
        if (!particles[i].active) continue;
        particles[i].x += particles[i].vx * DELTAT;
        particles[i].y += particles[i].vy * DELTAT;
        if (particles[i].x < 0) particles[i].x += side;
        if (particles[i].x >= side) particles[i].x -= side;
        if (particles[i].y < 0) particles[i].y += side;
        if (particles[i].y >= side) particles[i].y -= side;
    }
}

int check_collisions(particle_t *particles, long long n_part) {
    int collisions = 0;
    for (long long i = 0; i < n_part; i++) {
        if (!particles[i].active) continue;
        for (long long j = i + 1; j < n_part; j++) {
            if (!particles[j].active) continue;
            double dx = particles[j].x - particles[i].x;
            double dy = particles[j].y - particles[i].y;
            if (dx * dx + dy * dy < EPSILON2) {
                particles[i].active = 0;
                particles[j].active = 0;
                collisions++;
                break;
            }
        }
    }
    return collisions;
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Uso: %s <seed> <side> <grid_size> <num_particles> <time_steps>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long seed = atol(argv[1]);
    double side = atof(argv[2]);
    long ncside = atol(argv[3]);
    long long n_part = atoll(argv[4]);
    int time_steps = atoi(argv[5]);

    particle_t *particles = (particle_t *)malloc(n_part * sizeof(particle_t));
    if (!particles) {
        fprintf(stderr, "Erro ao alocar memória para partículas\n");
        return EXIT_FAILURE;
    }

    init_particles(seed, side, ncside, n_part, particles);

    double exec_time = -omp_get_wtime();
    int total_collisions = 0;

    for (int t = 0; t < time_steps; t++) {
        compute_forces(particles, n_part, side, ncside);
        update_positions(particles, n_part, side);
        total_collisions += check_collisions(particles, n_part);
    }

    exec_time += omp_get_wtime();
    fprintf(stderr, "%.1fs\n", exec_time);

    printf("%.3f %.3f\n", particles[0].x, particles[0].y);
    printf("%d\n", total_collisions);

    free(particles);
    return EXIT_SUCCESS;
}