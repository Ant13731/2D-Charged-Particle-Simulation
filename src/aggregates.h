#pragma once

#include "classes.h"
#include <cmath>

enum ParticleProperty
{
    speed,
    kinetic,
    electric
};

void get_speed_distribution(int maxwell_distribution[], int num_buckets, Particle current_particles[], int num_particles);
void get_kinetic_energy_distribution(int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles);
void get_electric_potential_energy_distribution(int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles);

float get_total_energy(Particle current_particles[], int num_particles);

float get_min(Particle current_particles[], int num_particles, ParticleProperty property);
float get_max(Particle current_particles[], int num_particles, ParticleProperty property);
float get_total(Particle current_particles[], int num_particles, ParticleProperty property);
