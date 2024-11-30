#include "classes.h"
#include "configurations.h"
#include <iostream>

// Func should do the following:
// Input - nothing - may ask for user input within the func as needed
// Output: list of particles and total num of particles

float preset_radius = 0.25;

Particle *random_configuration(int sqr_bounds, int &num_total_particles)
{
    int num_particles, num_charged_particles;
    std::cout << "How many particles would you like to simulate? ";
    std::cin >> num_particles;
    std::cout << "How many charged particles would you like to simulate? ";
    std::cin >> num_charged_particles;

    num_total_particles = num_particles + num_charged_particles;
    Particle *current_particles = new Particle[num_total_particles];

    for (int i = 0; i < num_particles; i++)
    {
        current_particles[i] = Particle::make_rand_particle(sqr_bounds);
    }
    for (int i = num_particles; i < num_total_particles; i++)
    {
        current_particles[i] = Particle::make_rand_charged_particle(sqr_bounds);
    }

    return current_particles;
}

Particle *uncharged_2_points_1D(int &num_total_particles)
{
    num_total_particles = 2;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(1, 0), Vec2D(-10, 0), 1, 0, preset_radius);
    current_particles[1] = Particle(Vec2D(-1, 0), Vec2D(10, 0), 1, 0, preset_radius);

    return current_particles;
}

Particle *uncharged_2_points_2D(int &num_total_particles)
{
    num_total_particles = 2;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(1, 0.124), Vec2D(-10, 0), 1, 0, preset_radius);
    current_particles[1] = Particle(Vec2D(-1, -0.124), Vec2D(10, 0), 1, 0, preset_radius);

    return current_particles;
}

Particle *charged_2_points_1D_same_charge(int &num_total_particles)
{
    num_total_particles = 2;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(1, 0), Vec2D(-1, 0), 1, 1, preset_radius);
    current_particles[1] = Particle(Vec2D(-1, 0), Vec2D(1, 0), 1, 1, preset_radius);

    return current_particles;
}

Particle *charged_2_points_1D_opposite_charge(int &num_total_particles)
{
    num_total_particles = 2;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(1, 0), Vec2D(-1, 0), 1, 1, preset_radius);
    current_particles[1] = Particle(Vec2D(-1, 0), Vec2D(1, 0), 1, -1, preset_radius);

    return current_particles;
}

Particle *charged_2_points_orbit(int &num_total_particles)
{
    num_total_particles = 2;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(0, 1), Vec2D(10, 0), 1, 1, preset_radius);
    current_particles[1] = Particle(Vec2D(0, -1), Vec2D(-10, 0), 1, -1, preset_radius);

    return current_particles;
}

Particle *charged_points_in_circle(int &num_total_particles)
{
    num_total_particles = 4;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(1, 0), Vec2D(0, 1), 1, 1, preset_radius);
    current_particles[1] = Particle(Vec2D(0, 1), Vec2D(-1, 0), 1, 1, preset_radius);
    current_particles[2] = Particle(Vec2D(-1, 0), Vec2D(0, -1), 1, 1, preset_radius);
    current_particles[3] = Particle(Vec2D(0, -1), Vec2D(1, 0), 1, 1, preset_radius);

    return current_particles;
}

Particle *charged_points_in_circle_no_velocity(int &num_total_particles)
{
    num_total_particles = 4;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(1, 0), Vec2D(0, 0), 1, 1, preset_radius);
    current_particles[1] = Particle(Vec2D(0, 1), Vec2D(0, 0), 1, 1, preset_radius);
    current_particles[2] = Particle(Vec2D(-1, 0), Vec2D(0, 0), 1, 1, preset_radius);
    current_particles[3] = Particle(Vec2D(0, -1), Vec2D(0, 0), 1, 1, preset_radius);

    return current_particles;
}

Particle *atom(int &num_total_particles)
{
    num_total_particles = 13;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(0, 0), Vec2D(0, 0), 100, 100, preset_radius);
    current_particles[1] = Particle(Vec2D(5, 0), Vec2D(0, -20), 1, -1, preset_radius);
    // current_particles[6] = Particle(Vec2D(5, -1), Vec2D(0, -20), 1, -1, preset_radius);
    // current_particles[7] = Particle(Vec2D(5, -2), Vec2D(0, -20), 1, -1, preset_radius);
    // current_particles[8] = Particle(Vec2D(5, -3), Vec2D(0, -20), 1, -1, preset_radius);
    current_particles[2] = Particle(Vec2D(-5, 0), Vec2D(0, 20), 1, -1, preset_radius);
    // current_particles[3] = Particle(Vec2D(-5, 1), Vec2D(0, 20), 1, -1, preset_radius);
    // current_particles[4] = Particle(Vec2D(-5, 2), Vec2D(0, 20), 1, -1, preset_radius);
    // current_particles[5] = Particle(Vec2D(-5, 3), Vec2D(0, 20), 1, -1, preset_radius);
    // current_particles[9] = Particle(Vec2D(-1, 1), Vec2D(0, 20), 1, -1, preset_radius);
    // current_particles[10] = Particle(Vec2D(-1, 1.5), Vec2D(0, 20), 1, -1, preset_radius);
    // current_particles[11] = Particle(Vec2D(-1, 2), Vec2D(0, 20), 1, -1, preset_radius);
    // current_particles[12] = Particle(Vec2D(-1, 2.5), Vec2D(0, 20), 1, -1, preset_radius);
    // current_particles[3] = Particle(Vec2D(0, 5), Vec2D(20, 0), 1, -1, preset_radius);
    // current_particles[4] = Particle(Vec2D(0, -5), Vec2D(-20, 0), 1, -1, preset_radius);

    return current_particles;
}