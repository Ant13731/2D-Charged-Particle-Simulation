#include "ode.h"
#include "classes.h"
#include "cpgplot.h"
#include <iostream>
#include <ctime>
// #include <thread>
// #include <chrono>

int main()
{
    // Configuration
    float dt = 0.1;
    float sqr_bounds = 10.;
    int num_particles = 2;
    int num_charged_particles = 0;
    int num_total_particles = num_particles + num_charged_particles;
    Particle current_particles[num_total_particles];
    Particle next_particles[num_total_particles];
    time_t iteration_timer;
    char input_ch;
    float input_x, input_y;

    // Step 1: Initialize the plot background
    // Open a plot window
    if (!cpgopen("/XWINDOW"))
        return 1;

    // cpgpage();
    // cpgsvp(0.05, 0.95, 0.05, 0.95);
    // cpgwnad(0.0, 1.0, 0.0, 1.0);

    // Set up white background, line thickness and text size
    cpgscr(0, 1.0, 1.0, 1.0); // index 0, background colour
    cpgscr(1, .0, .0, .0);    // index 1, default fg colour
    cpgslw(5);                // line width
    cpgsch(1.5);              // text size

    cpgenv(-sqr_bounds * 1.1, sqr_bounds * 1.1, -sqr_bounds * 1.1, sqr_bounds * 1.1, 0, 1);

    // Step 2: Make starting particles
    for (int i = 0; i < num_particles; i++)
    {
        current_particles[i] = Particle::make_rand_particle(sqr_bounds);
    }
    for (int i = num_particles; i < num_total_particles; i++)
    {
        current_particles[i] = ChargedParticle::make_rand_particle(sqr_bounds);
    }

    // Step 3: While user has not exited the program
    for (;;)
    {
        // - Step 4: Plot the particles
        for (int i = 0; i < num_total_particles; i++)
        {
            if (current_particles[i].is_charged())
                cpgsci(0);
            else if (reinterpret_cast<ChargedParticle *>(current_particles)[i].charge > 0)
                cpgsci(2);
            else
                cpgsci(4);
            cpgpt1(current_particles[i].position.x, current_particles[i].position.y, 17);
        }
        // - Step 5: Start time delta
        iteration_timer = time(NULL);

        // - Step 6: Update the positions of the particles by time delta
        for (int i = 0; i < num_total_particles; i++)
        {
            // TODO dont use clone, just make 2 sets of objects and continually update
            next_particles[i] = current_particles[i].clone();
        }

        for (int i = 0; i < num_total_particles; i++)
        {
            Vec2D velocity_contributions_for_i = Vec2D();
            Vec2D acceleration_contributions_for_i = Vec2D();
            for (int j = 0; j < num_total_particles; j++)
            {
                if (i == j)
                    continue;
                velocity_contributions_for_i += current_particles[i].get_velocity_contributions(current_particles[j]);
                if (current_particles[i].is_charged())
                    acceleration_contributions_for_i += (reinterpret_cast<ChargedParticle *>(current_particles)[i]).get_acceleration_contributions(current_particles[j]);
            }

            next_particles[i].velocity += velocity_contributions_for_i;
            // No acceleration lingers from previous time (use = instead of +=)? only acceleration for charged particles should be other charged particles
            if (next_particles[i].is_charged())
                next_particles[i].acceleration = acceleration_contributions_for_i;

            Vec2D v_i_half = get_next_half_velocity(next_particles[i].velocity, next_particles[i].acceleration, dt);
            next_particles[i].position = get_next_position(next_particles[i].position, v_i_half, dt);
            // Should this acceleration be the next term in the series? It should be according to leapfrog
            next_particles[i].velocity = get_next_half_velocity(v_i_half, next_particles[i].acceleration, dt);
        }

        for (int i = 0; i < num_total_particles; i++)
        {
            current_particles[i] = next_particles[i].clone();
        }

        // - Step 7: Wait for rest of time delta (idle loop)
        if (!cpgcurs(&input_x, &input_y, &input_ch))
            break;

        // 'x' corresponds to a right click: zoom out
        if (input_ch == 'x' || input_ch == 'X' || input_ch == 'd' || input_ch == 'D')
        {
            std::cout << "Advancing dt by " << dt << "seconds" << std::endl;
            continue;
        }

        // space or 'q' quits
        if (input_ch == ' ' || input_ch == 'q' || input_ch == 'Q')
        {
            return 0;
        }
        // while (time(NULL) - iteration_timer < dt)
        // {
        //     // std::this_thread::sleep_for(std::chrono::milliseconds(x * 1000 / 2));
        // }
    }
}