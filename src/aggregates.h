#pragma once

#include "classes.h"
#include <cmath>

// Enum for the different properties of a particle that can be aggregated
enum ParticleProperty
{
    speed,
    kinetic,
    electric
};

// Get the speed distribution of all particles, separated into 30 containers
void get_speed_distribution(int maxwell_distribution[], int num_buckets, Particle current_particles[], int num_particles);

// Get the total energy of all particles (kinetic + electric potential)
float get_total_energy(Particle current_particles[], int num_particles);

// Get the minimum value of a property for all particles
float get_min(Particle current_particles[], int num_particles, ParticleProperty property);

// Get the maximum value of a property for all particles
float get_max(Particle current_particles[], int num_particles, ParticleProperty property);

/*
 * Get the total value of a property for all particles.
 * For speed and kinetic energy, this is the sum of the property for all particles.
 * For electric potential energy, this is the sum of the electric potential energy between all pairs of particles.
 */
float get_total(Particle current_particles[], int num_particles, ParticleProperty property);

// void get_kinetic_energy_distribution(int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles);
// void get_electric_potential_energy_distribution(int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles);
