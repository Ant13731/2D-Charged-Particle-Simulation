#pragma once

#include "classes.h"
#include <cmath>

void get_speed_distribution(float x_axis[], int maxwell_distribution[], int num_buckets, Particle current_particles[], int num_particles);
void get_kinetic_energy_distribution(float x_axis[], int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles);
void get_electric_potential_energy_distribution(float x_axis[], int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles);

float get_total_speed(Particle current_particles[], int num_particles);
float get_total_kinetic_energy(Particle current_particles[], int num_particles);
float get_total_electric_potential_energy(Particle current_particles[], int num_particles);
float get_total_energy(Particle current_particles[], int num_particles);

float get_max_speed(Particle current_particles[], int num_particles);
float get_max_kinetic_energy(Particle current_particles[], int num_particles);
float get_max_electric_potential_energy(Particle current_particles[], int num_particles);

float get_min_speed(Particle current_particles[], int num_particles);
float get_min_kinetic_energy(Particle current_particles[], int num_particles);
float get_min_electric_potential_energy(Particle current_particles[], int num_particles);