#pragma once
#include "classes.h"

Particle *random_configuration(int sqr_bounds, int &num_total_particles);

Particle *uncharged_2_points_1D(int &num_total_particles);
Particle *uncharged_2_points_2D(int &num_total_particles);
Particle *charged_2_points_1D_same_charge(int &num_total_particles);
Particle *charged_2_points_1D_opposite_charge(int &num_total_particles);
Particle *charged_2_points_orbit(int &num_total_particles);
Particle *charged_points_in_circle(int &num_total_particles);
Particle *charged_points_in_circle_no_velocity(int &num_total_particles);

Particle *atom(int &num_total_particles);
