#include "ode.h"
#include "classes.h"
#include "cpgplot.h"
#include "table.h"
#include "aggregates.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include "configurations.h"

// PGPlot helpers
void setup_plot()
{
    // Set up white background, line thickness and text size
    cpgscr(0, 1.0, 1.0, 1.0); // index 0, background colour
    cpgscr(1, .0, .0, .0);    // index 1, default fg colour
    cpgslw(3);                // line width
    cpgsch(1.5);              // text size
    cpgask(0);                // no more user input
}
void setup_distribution_plot(int distribution_buckets, int num_total_particles)
{
    // Set up distribution plots
    cpgenv(0, distribution_buckets, 0, std::max(5, num_total_particles / 3), 0, 1);
}

void plot_distribution(
    int distribution[],
    int num_buckets,
    std::string title,
    std::string x_label,
    std::string y_label)
{
    // Actually plot the distribution on the current plot device
    cpgeras();
    cpgsci(1);                                               // Set colour to black
    cpgbox("BCTCN", 0, 0, "BCTCN", 0, 0);                    // Draw the box
    cpglab(x_label.c_str(), y_label.c_str(), title.c_str()); // Redo axis labels since they were erased

    for (int i = 0; i < num_buckets; i++)
    {
        cpgsci(i + 2);
        cpgrect(i, i + 1, 0, distribution[i]); // Plot the number of particles
    }
}

int main()
{

    // Configuration
    float dt = 0.01;
    float sqr_bounds = 10.;
    // int num_particles = 50;
    // int num_charged_particles = 50;

    // Pgplot variables
    char input_ch;
    float input_x, input_y;
    std::chrono::steady_clock iteration_timer;

    RectangleContainer container = RectangleContainer(-sqr_bounds, sqr_bounds, sqr_bounds, -sqr_bounds);

    int num_total_particles;
    Particle *current_particles;

    int configuration_choice;
    std::cout << "Choose a configuration:\n"
              << "1. Random configuration\n"
              << "2. 2 uncharged particles in 1D\n"
              << "3. 2 uncharged particles in 2D\n"
              << "4. 2 charged particles in 1D with same charge\n"
              << "5. 2 charged particles in 1D with opposite charge\n"
              << "6. 2 charged particles in orbit\n"
              << "7. Charged particles in a circle\n"
              << "8. Charged particles in a circle with no velocity\n"
              << "9. Atom\n";

    std::cin >> configuration_choice;
    switch (configuration_choice)
    {
    case 1:
        current_particles = random_configuration(sqr_bounds, num_total_particles);
        break;
    case 2:
        current_particles = uncharged_2_points_1D(num_total_particles);
        break;
    case 3:
        current_particles = uncharged_2_points_2D(num_total_particles);
        break;
    case 4:
        current_particles = charged_2_points_1D_same_charge(num_total_particles);
        break;
    case 5:
        current_particles = charged_2_points_1D_opposite_charge(num_total_particles);
        break;
    case 6:
        current_particles = charged_2_points_orbit(num_total_particles);
        break;
    case 7:
        current_particles = charged_points_in_circle(num_total_particles);
        break;
    case 8:
        current_particles = charged_points_in_circle_no_velocity(num_total_particles);
        break;
    case 9:
        current_particles = atom(num_total_particles);
        break;
    default:
        std::cout << "Invalid choice\n";
        return 1;
    }

    Particle prev_particles[num_total_particles];

    // int num_total_particles = num_particles + num_charged_particles;
    // Particle next_particles[num_total_particles];
    // int recent_collisions[num_total_particles][num_total_particles];

    // float x_axis[distribution_buckets];

    // Distribution graph variables
    int distribution_buckets = 30;
    int speed_distribution[distribution_buckets];
    int k_energy_distribution[distribution_buckets];
    int e_energy_distribution[distribution_buckets];

    // Energy over time
    std::vector<float> total_speed;
    std::vector<float> total_energy;
    std::vector<float> total_kinetic_energy;
    std::vector<float> total_electric_energy;

    // Step 1: Initialize the plot background
    // Open a plot window for the particles and their distributions
    // int k_energy_distribution_plot = cpgopen("/XWINDOW");
    int speed_distribution_plot = cpgopen("/XWINDOW");
    int energy_over_time_plot = cpgopen("/XWINDOW");
    int particle_plot = cpgopen("/XWINDOW");
    // int e_energy_distribution_plot = cpgopen("/XWINDOW");
    if (!particle_plot ||
        !speed_distribution_plot ||
        // !k_energy_distribution_plot ||
        !energy_over_time_plot)
    //  ||
    // !e_energy_distribution_plot)
    {
        std::cout << "Could not open plot windows\n";
        return 1;
    }

    // Set up backgrounds for each plot
    cpgslct(particle_plot);
    setup_plot();
    cpgenv(-sqr_bounds, sqr_bounds, -sqr_bounds, sqr_bounds, 0, 1);

    cpgslct(speed_distribution_plot);
    setup_plot();
    setup_distribution_plot(distribution_buckets, num_total_particles);

    // cpgslct(k_energy_distribution_plot);
    // setup_plot();
    // setup_distribution_plot(distribution_buckets, num_total_particles);

    cpgslct(energy_over_time_plot);
    setup_plot();
    cpgenv(0, 1, -num_total_particles * 2, num_total_particles * 50, 0, 1); // 7000 seems good for 200 particles

    // Particle variables
    // std::cout << "How many particles would you like to simulate? ";
    // std::cin >> num_particles;
    // std::cout << "How many charged particles would you like to simulate? ";
    // std::cin >> num_charged_particles;

    // cpgslct(e_energy_distribution_plot);
    // setup_plot();
    // setup_distribution_plot(distribution_buckets, num_total_particles);

    // Step 2: Make starting particles (randomly)
    // for (int i = 0; i < num_particles; i++)
    // {
    //     current_particles[i] = Particle::make_rand_particle(sqr_bounds);
    // }
    // for (int i = num_particles; i < num_total_particles; i++)
    // {
    //     current_particles[i] = Particle::make_rand_charged_particle(sqr_bounds);
    // }
    // for (int i = 0; i < num_total_particles; i++)
    // {
    //     for (int j = 0; j < num_total_particles; j++)
    //     {
    //         recent_collisions[i][j] = 0;
    //     }
    // }

    // current_particles[0] = Particle(Vec2D(1, 0), Vec2D(-1, 0), 1, 0);
    // current_particles[1] = Particle(Vec2D(-1, 0.005), Vec2D(1, 0), 1, 0);

    // Step 3: While user has not exited the program
    std::string axis_opts = "BC";
    for (int counter = 0;; counter++)
    {
        // Redraw the particle plot
        cpgslct(particle_plot);
        cpgeras();
        cpgslw(3);
        cpgsci(1);
        cpgbox(axis_opts.c_str(), 0.0, 0, axis_opts.c_str(), 0.0, 0);
        cpgslw(20);

        // timer to make the graph update smoothly, every dt seconds
        auto iteration_timer = std::chrono::high_resolution_clock::now();

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
            if (num_total_particles <= 6 && configuration_choice == 1)
                std::cout << current_particles[i].to_string() << std::endl;
        }

        // - Step 6: Update the positions of the particles by time delta
        // for (int i = 0; i < num_total_particles; i++)
        // {
        //     // TODO dont use clone, just make 2 sets of objects and continually update
        //     next_particles[i] = current_particles[i].clone();
        // }

        // Update positions and collisions
        // for (int i = 0; i < num_total_particles; i++)
        // {

        //     // Update collisions and particle-particle interactions
        //     Vec2D velocity_contributions_for_i = Vec2D();
        //     Vec2D acceleration_contributions_for_i = Vec2D();
        //     for (int j = 0; j < num_total_particles; j++)
        //     {

        //         if (i == j)
        //             continue;
        //         // let charged particles sort themselves out with acceleration alone
        //         if (!current_particles[i].is_charged() || !current_particles[j].is_charged())
        //         {
        //             // if (recent_collisions[i][j] < counter - 1)
        //             // {
        //             velocity_contributions_for_i += current_particles[i].get_velocity_contributions(current_particles[j]);
        //             // }
        //             // if (current_particles[i].particles_collided(current_particles[j]))
        //             // {
        //             //     recent_collisions[i][j] = counter;
        //             // }
        //         }
        //         acceleration_contributions_for_i += current_particles[i].get_acceleration_contributions(current_particles[j]);
        //     }

        //     next_particles[i].velocity += velocity_contributions_for_i;
        //     // No acceleration lingers from previous time (use = instead of +=)? only acceleration for charged particles should be other charged particles
        //     next_particles[i].acceleration = acceleration_contributions_for_i;
        //     next_particles[i].velocity = container.get_collision_velocity(next_particles[i]);

        //     Vec2D v_i_half = get_next_half_velocity(next_particles[i].velocity, next_particles[i].acceleration, dt);
        //     next_particles[i].position = get_next_position(next_particles[i].position, v_i_half, dt);
        //     // Should this acceleration be the next term in the series? It should be according to leapfrog
        //     next_particles[i].velocity = get_next_half_velocity(v_i_half, next_particles[i].acceleration, dt);
        // }

        // Swap in new calculations for all particles
        // for (int i = 0; i < num_total_particles; i++)
        // {
        //     current_particles[i] = next_particles[i].clone();
        // }

        for (int i = 0; i < num_total_particles; i++)
        {
            for (int j = i; j < num_total_particles; j++)
            {

                if (i == j)
                    continue;

                // if (!current_particles[i].is_charged() || !current_particles[j].is_charged())
                // {
                Vec2D temp = current_particles[i].get_velocity_contributions(current_particles[j]);
                current_particles[j].velocity += current_particles[j].get_velocity_contributions(current_particles[i]);
                current_particles[i].velocity += temp;
                // }

                // current_particles[i].acceleration += current_particles[i].get_acceleration_contributions(current_particles[j]);
                // current_particles[j].acceleration += current_particles[j].get_acceleration_contributions(current_particles[i]);
            }

            // Update collisions and particle-particle interactions
            // Vec2D velocity_contributions_for_i = Vec2D();
            // Vec2D acceleration_contributions_for_i = Vec2D();
            // for (int j = 0; j < num_total_particles; j++)
            // {

            //     if (i == j)
            //         continue;
            //     // let charged particles sort themselves out with acceleration alone
            //     if (!current_particles[i].is_charged() || !current_particles[j].is_charged())
            //     {
            //         // if (recent_collisions[i][j] < counter - 1)
            //         // {
            //         velocity_contributions_for_i += current_particles[i].get_velocity_contributions(current_particles[j]);
            //         // }
            //         // if (current_particles[i].particles_collided(current_particles[j]))
            //         // {
            //         //     recent_collisions[i][j] = counter;
            //         // }
            //     }
            //     acceleration_contributions_for_i += current_particles[i].get_acceleration_contributions(current_particles[j]);
            // }

            // next_particles[i].velocity += velocity_contributions_for_i;
            // No acceleration lingers from previous time (use = instead of +=)? only acceleration for charged particles should be other charged particles
            // next_particles[i].acceleration = acceleration_contributions_for_i;
        }
        for (int i = 0; i < num_total_particles; i++)
            current_particles[i].velocity = container.get_collision_velocity(current_particles[i]);

        for (int i = 0; i < num_total_particles; i++)
        {
            prev_particles[i] = current_particles[i].clone();
        }

        for (int i = 0; i < num_total_particles; i++)
        {
            current_particles[i].acceleration.zero();
        }

        for (int i = 0; i < num_total_particles; i++)
        {
            for (int j = 0; j < num_total_particles; j++)
            {
                if (i == j)
                    continue;
                current_particles[i].acceleration += current_particles[i].get_acceleration_contributions(current_particles[j]);
            }
        }

        for (int i = 0; i < num_total_particles; i++)
        {
            // TODO make this the previous acceleration?????????????????
            Vec2D v_i_half = get_next_half_velocity(current_particles[i].velocity, prev_particles[i].acceleration, dt);
            // Vec2D v_i_half = get_next_half_velocity(current_particles[i].velocity, current_particles[i].acceleration, dt);
            current_particles[i].position = get_next_position(current_particles[i].position, v_i_half, dt);
            current_particles[i].velocity = get_next_half_velocity(v_i_half, current_particles[i].acceleration, dt);
        }

        // Debugging table for most recent collision, only for small numbers of particles
        // if (num_total_particles <= 6)
        // {
        //     TextTable t('-', '|', '+');
        //     t.add("");
        //     for (int i = 0; i < num_total_particles; i++)
        //     {
        //         t.add("Particle " + std::to_string(i));
        //     }
        //     t.endOfRow();
        //     for (int i = 0; i < num_total_particles; i++)
        //     {
        //         t.add("Particle " + std::to_string(i));
        //         for (int j = 0; j < num_total_particles; j++)
        //         {
        //             t.add(std::to_string(recent_collisions[i][j]));
        //         }
        //         t.endOfRow();
        //     }
        //     std::cout << t;
        // }

        float delta_k = counter == 0 ? 0.f : total_kinetic_energy.back();
        float delta_u = counter == 0 ? 0.f : total_electric_energy.back();

        // Useful output info each iteration
        total_speed.push_back(get_total(current_particles, num_total_particles, ParticleProperty::speed));
        total_kinetic_energy.push_back(get_total(current_particles, num_total_particles, ParticleProperty::kinetic));
        total_electric_energy.push_back(get_total(current_particles, num_total_particles, ParticleProperty::electric));
        total_energy.push_back(get_total_energy(current_particles, num_total_particles));

        delta_k = total_kinetic_energy.back() - delta_k;
        delta_u = total_electric_energy.back() - delta_u;

        std::cout << "Total speed: " << total_speed.back() << "\n";
        std::cout << "Total energy k: " << total_kinetic_energy.back() << "\n";
        std::cout << "Total energy q: " << total_electric_energy.back() << "\n";
        std::cout << "Total energy: " << total_energy.back() << "\n";
        std::cout << "Delta k: " << delta_k << "\n";
        std::cout << "Delta u: " << delta_u << "\n";
        // std::cout << "t:q ratio: " << (total_energy.back() - total_kinetic_energy.back()) / total_electric_energy.back() << "\n";

        // Plot energy over time
        cpgslct(energy_over_time_plot);
        cpgeras();
        cpgsci(1);
        cpgbox("BCT", 0, 0, "BCTN", 0, 0);
        cpglab("Time", "Energy", "Energy Over Time");

        if (total_speed.size() > 5000)
        {
            total_speed.erase(total_speed.begin());
            total_energy.erase(total_energy.begin());
            total_kinetic_energy.erase(total_kinetic_energy.begin());
            total_electric_energy.erase(total_electric_energy.begin());
        }

        std::vector<float> x_axis_vec(total_speed.size());
        for (int i = 0; i < total_speed.size(); i++)
        {
            x_axis_vec[i] = (float)i / (float)total_speed.size();
        }

        cpgsci(3);
        cpgline(total_speed.size(), &x_axis_vec[0], &total_speed[0]);
        cpgsci(1);
        cpgline(total_energy.size(), &x_axis_vec[0], &total_energy[0]);
        cpgsci(5);
        cpgline(total_kinetic_energy.size(), &x_axis_vec[0], &total_kinetic_energy[0]);
        cpgsci(6);
        cpgline(total_electric_energy.size(), &x_axis_vec[0], &total_electric_energy[0]);

        // Plot distributions
        cpgslct(speed_distribution_plot);
        get_speed_distribution(speed_distribution, distribution_buckets, current_particles, num_total_particles);
        // get_speed_distribution(x_axis, speed_distribution, distribution_buckets, current_particles, num_total_particles);
        plot_distribution(
            // x_axis,
            speed_distribution,
            distribution_buckets,
            "Speed Distribution",
            "Speed",
            "Number of Particles");

        // cpgslct(k_energy_distribution_plot);
        // get_kinetic_energy_distribution(k_energy_distribution, distribution_buckets, current_particles, num_total_particles);
        // // get_kinetic_energy_distribution(x_axis, k_energy_distribution, distribution_buckets, current_particles, num_total_particles);
        // plot_distribution(
        //     // x_axis,
        //     k_energy_distribution,
        //     distribution_buckets,
        //     "Kinetic Energy Distribution",
        //     "Kinetic Energy",
        //     "Number of Particles");

        // cpgslct(e_energy_distribution_plot);
        // get_electric_potential_energy_distribution(x_axis, e_energy_distribution, distribution_buckets, current_particles, num_total_particles);
        // plot_distribution(
        //     x_axis,
        //     e_energy_distribution,
        //     distribution_buckets,
        //     "Electric Potential Energy Distribution",
        //     "Electric Potential Energy",
        //     "Number of Particles");

        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - iteration_timer).count() < dt * 5000)
        {
            // idle
        }

        // // Old code to update only on keypress - automatic updates seem to work better though
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
    delete[] current_particles;
}