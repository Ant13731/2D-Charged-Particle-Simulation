#pragma once
#include "classes.h"

Particle *random_configuration(int sqr_bounds, int &num_total_particles);

Particle *uncharged_2_points_1D(int &num_total_particles);
/* Two particles meet at a 90-degree angle*/
Particle *uncharged_2_points_2D(int &num_total_particles);
Particle *charged_2_points_1D_same_charge(int &num_total_particles);
Particle *charged_2_points_1D_opposite_charge(int &num_total_particles);
/* Oppositely charged objects orbiting one another*/
Particle *charged_2_points_orbit(int &num_total_particles);
/*4 particles initially in a cross shape, rotating and moving away from one another*/
Particle *charged_points_in_circle(int &num_total_particles);
/*Same as above but no starting velocity - oscillates between meeting at the origin and then bouncing off the walls, like a cross shape*/
Particle *charged_points_in_circle_no_velocity(int &num_total_particles);

/*Two small particles orbit one large particle*/
Particle *atom(int &num_total_particles);
