#include "ode.h"
#include "classes.h"
#include "cpgplot.h"
#include "table.h"
#include "aggregates.h"
#include <iostream>
#include <ctime>
#include <chrono>
/*
Current problems:
1. does recreating Particles in the array waste a lot of memory? If so,
    just make two arrays at the beginning and continuously update the values
2. particles fly away if they gain too much acceleration - should I put a cap on that?
3. graph not clearing properly
4. If collisions happen too slowly, the velocity of particles will be contributed more than once.
    This makes the particles gain a sudden burst of velocity and fly away
    - Solution: make a list of particles that have already collided with the current particle.
        Then we only allow those particles to collide again if they havent collided for more than one step
    - Solution: see if the velocity vectors are still pointing towards each other
    - Solution: dont use these equations at all - instead calculate force?
        https://gamedev.stackexchange.com/questions/32611/what-is-the-best-way-to-handle-simultaneous-collisions-in-a-physics-engine

TODO:
- visualize maxwell boltzmann distribution on the same page as particles moving - how to do that?
- measure the energy of the system over time (to make sure the charges dont go too crazy)
- measure momentum of the system over time
- plot both of those for all, uncharged, and charged particles
-/ make graph automatically play
- make a random particle generator that sets a certain momentum and total energy

*/

int main()
{

    // Configuration
    float dt = 0.01;
    float sqr_bounds = 10.;
    int num_particles = 50;
    int num_charged_particles = 50;
    // Pgplot variables
    char input_ch;
    float input_x, input_y;
    std::chrono::steady_clock iteration_timer;

    std::cout << "How many particles would you like to simulate? ";
    std::cin >> num_particles;
    std::cout << "How many charged particles would you like to simulate? ";
    std::cin >> num_charged_particles;

    int num_total_particles = num_particles + num_charged_particles;
    Particle current_particles[num_total_particles];
    Particle next_particles[num_total_particles];
    int recent_collisions[num_total_particles][num_total_particles];
    RectangleContainer container = RectangleContainer(-sqr_bounds, sqr_bounds, sqr_bounds, -sqr_bounds);

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
    cpgslw(20);               // line width
    cpgsch(1.5);              // text size

    // Step 2: Make starting particles
    for (int i = 0; i < num_particles; i++)
    {
        current_particles[i] = Particle::make_rand_particle(sqr_bounds);
    }
    for (int i = num_particles; i < num_total_particles; i++)
    {
        current_particles[i] = Particle::make_rand_charged_particle(sqr_bounds);
    }
    for (int i = 0; i < num_total_particles; i++)
    {
        for (int j = 0; j < num_total_particles; j++)
        {
            recent_collisions[i][j] = 0;
        }
    }

    // current_particles[0] = Particle(Vec2D(1, 0), Vec2D(-1, 0), 1, 0);
    // current_particles[1] = Particle(Vec2D(-1, 0.005), Vec2D(1, 0), 1, 0);

    cpgenv(-sqr_bounds * 1.1, sqr_bounds * 1.1, -sqr_bounds * 1.1, sqr_bounds * 1.1, 0, 1);
    // Step 3: While user has not exited the program
    for (int counter = 0;; counter++)
    {
        cpgeras();

        auto iteration_timer = std::chrono::high_resolution_clock::now();

        // iteration_timer = time(NULL);
        // - Step 4: Plot the particles
        std::cout << "Plotting particles: " << counter << "\n";
        for (int i = 0; i < num_total_particles; i++)
        {
            if (!current_particles[i].is_charged())
                cpgsci(1);
            else if (current_particles[i].charge > 0)
                cpgsci(2);
            else
                cpgsci(4);
            cpgpt1(current_particles[i].position.x, current_particles[i].position.y, -1);
            if (num_total_particles <= 6)
                std::cout << current_particles[i].to_string() << std::endl;
        }
        // - Step 5: Start time delta

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
                // let charged particles sort themselves out with acceleration alone
                if (!current_particles[i].is_charged() || !current_particles[j].is_charged())
                {
                    if (recent_collisions[i][j] < counter - 1)
                    {
                        velocity_contributions_for_i += current_particles[i].get_velocity_contributions(current_particles[j]);
                    }
                    if (current_particles[i].particles_collided(current_particles[j]))
                    {
                        recent_collisions[i][j] = counter;
                    }
                }
                acceleration_contributions_for_i += current_particles[i].get_acceleration_contributions(current_particles[j]);
            }

            next_particles[i].velocity += velocity_contributions_for_i;
            // No acceleration lingers from previous time (use = instead of +=)? only acceleration for charged particles should be other charged particles
            // if (next_particles[i].is_charged())
            next_particles[i].acceleration = acceleration_contributions_for_i;
            next_particles[i].velocity = container.get_collision_velocity(next_particles[i]);

            Vec2D v_i_half = get_next_half_velocity(next_particles[i].velocity, next_particles[i].acceleration, dt);
            next_particles[i].position = get_next_position(next_particles[i].position, v_i_half, dt);
            // Should this acceleration be the next term in the series? It should be according to leapfrog
            next_particles[i].velocity = get_next_half_velocity(v_i_half, next_particles[i].acceleration, dt);
        }

        for (int i = 0; i < num_total_particles; i++)
        {
            current_particles[i] = next_particles[i].clone();
        }

        if (num_total_particles <= 6)
        {
            TextTable t('-', '|', '+');
            t.add("");
            for (int i = 0; i < num_total_particles; i++)
            {
                t.add("Particle " + std::to_string(i));
            }
            t.endOfRow();
            for (int i = 0; i < num_total_particles; i++)
            {
                t.add("Particle " + std::to_string(i));
                for (int j = 0; j < num_total_particles; j++)
                {
                    t.add(std::to_string(recent_collisions[i][j]));
                }
                t.endOfRow();
            }
            std::cout << t;
        }

        std::cout << "Total speed: " << get_total_speed(current_particles, num_total_particles) << "\n";
        std::cout << "Total energy k: " << get_total_kinetic_energy(current_particles, num_total_particles) << "\n";
        std::cout << "Total energy q: " << get_total_electric_potential_energy(current_particles, num_total_particles) << "\n";
        std::cout << "Total energy: " << get_total_energy(current_particles, num_total_particles) << "\n";

        // auto finish = std::chrono::high_resolution_clock::now();
        // std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - iteration_timer).count() < dt * 5000)
        // time(NULL) - iteration_timer < dt / 10000.)
        {
            // std::cout << "Idle" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - iteration_timer).count() << "\n";
            // std::this_thread::sleep_for(std::chrono::milliseconds(x * 1000 / 2));
        }
        // - Step 7: Wait for rest of time delta (idle loop)
        // if (!cpgcurs(&input_x, &input_y, &input_ch))
        //     break;

        // // 'x' corresponds to a right click: zoom out
        // if (input_ch == 'x' || input_ch == 'X' || input_ch == 'd' || input_ch == 'D')
        // {
        //     // std::cout << "Advancing dt by " << dt << "seconds" << std::endl;
        //     continue;
        // }

        // // space or 'q' quits
        // if (input_ch == ' ' || input_ch == 'q' || input_ch == 'Q')
        // {
        //     return 0;
        // }
        // while (time(NULL) - iteration_timer < dt)
        // {
        //     // std::this_thread::sleep_for(std::chrono::milliseconds(x * 1000 / 2));
        // }
    }
}