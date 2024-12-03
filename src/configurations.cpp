#include "classes.h"
#include "configurations.h"
#include <iostream>
#include <cmath>

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

    current_particles[0] = Particle(Vec2D(1, 0), Vec2D(-8, 0), 1, 0, preset_radius);
    current_particles[1] = Particle(Vec2D(-1, 0), Vec2D(8, 0), 1, 0, preset_radius);

    return current_particles;
}

Particle *uncharged_2_points_2D(int &num_total_particles)
{
    num_total_particles = 2;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(1, 0), Vec2D(-8, 0), 1, 0, preset_radius);
    current_particles[1] = Particle(Vec2D(0, 1), Vec2D(0, -8), 1, 0, preset_radius);

    return current_particles;
}

Particle *charged_2_points_1D_same_charge(int &num_total_particles)
{
    num_total_particles = 2;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(1, 0), Vec2D(-5, 0), 1, 3, preset_radius);
    current_particles[1] = Particle(Vec2D(-1, 0), Vec2D(5, 0), 1, 3, preset_radius);

    return current_particles;
}

Particle *charged_2_points_1D_opposite_charge(int &num_total_particles)
{
    num_total_particles = 2;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(1, 0), Vec2D(-5, 0), 1, 3, preset_radius);
    current_particles[1] = Particle(Vec2D(-1, 0), Vec2D(5, 0), 1, -3, preset_radius);

    return current_particles;
}

Particle *charged_2_points_orbit(int &num_total_particles)
{
    num_total_particles = 2;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(0, 1), Vec2D(5, 0), 1, 5, preset_radius);
    current_particles[1] = Particle(Vec2D(0, -1), Vec2D(-5, 0), 1, -5, preset_radius);

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
    num_total_particles = 3;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(0, 0), Vec2D(0, 0), 100, 400, preset_radius);
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

Particle *pool(int &num_total_particles)
{
    num_total_particles = 226;
    Particle *current_particles = new Particle[num_total_particles];

    current_particles[0] = Particle(Vec2D(-10, 0), Vec2D(100, 0), 1, 0, preset_radius);

    // Create 200 particles ranging from 0 to 10 in the x direction, spaced 0.3 units apart
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            current_particles[1 + i * 15 + j] = Particle(Vec2D(j * .5f, i * .5f), Vec2D(0, 0), 1, 0, preset_radius);
            float x = current_particles[1 + i * 15 + j].position.x;
            float y = current_particles[1 + i * 15 + j].position.y;
            current_particles[1 + i * 15 + j].position.x = x * std::cos(M_PI / 4) - y * std::sin(M_PI / 4) + 5;
            current_particles[1 + i * 15 + j].position.y = x * std::sin(M_PI / 4) + y * std::cos(M_PI / 4) - 5;
        }
    }

    return current_particles;
}