#include "classes.h"
#include "aggregates.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm>
#include <stdexcept>

float get_min(Particle current_particles[], int num_particles, ParticleProperty property)
{
    float min = std::numeric_limits<float>::max();
    for (int i = 0; i < num_particles; i++)
    {
        switch (property)
        {
        case speed:
            min = std::min(min, current_particles[i].get_speed());
            break;
        case kinetic:
            min = std::min(min, current_particles[i].get_kinetic_energy());
            break;
        default:
            std::cout << "Property " << property << std::endl;
            throw std::invalid_argument("Property not supported");
        }
    }
    return min;
}

float get_max(Particle current_particles[], int num_particles, ParticleProperty property)
{
    float max = std::numeric_limits<float>::min();
    for (int i = 0; i < num_particles; i++)
    {
        switch (property)
        {
        case speed:
            max = std::max(max, current_particles[i].get_speed());
            break;
        case kinetic:
            max = std::max(max, current_particles[i].get_kinetic_energy());
            break;
        default:
            std::cout << "Property " << property << std::endl;
            throw std::invalid_argument("Property not supported");
        }
    }
    return max;
}

float get_total(Particle current_particles[], int num_particles, ParticleProperty property)
{
    float total = 0;
    if (property == electric)
    {
        for (int i = 0; i < num_particles; i++)
        {
            for (int j = 0; j < num_particles; j++)
            {
                if (i == j)
                    continue;

                // Calculation from https://phys.libretexts.org/Bookshelves/University_Physics/University_Physics_(OpenStax)/University_Physics_II_-_Thermodynamics_Electricity_and_Magnetism_(OpenStax)/07%3A_Electric_Potential/7.02%3A_Electric_Potential_Energy
                total += current_particles[i].charge * current_particles[j].charge / std::abs((current_particles[i].position - current_particles[j].position).length() + Particle::acceleration_epsilon);

                // Old method (attempted to simply add pairwise electric potential)
                // std::cout << "Calculating electric potential energy between particles " << i << " and " << j << ": " << current_particles[i].get_electric_potential_energy(current_particles[j]) << std::endl;
                // total += current_particles[i].get_electric_potential_energy(current_particles[j]) / current_particles[i].k;
            }
        }
        return Particle::k * total * 0.5f;
    }

    for (int i = 0; i < num_particles; i++)
    {
        switch (property)
        {
        case speed:
            total += current_particles[i].get_speed();
            break;
        case kinetic:
            total += current_particles[i].get_kinetic_energy();
            break;
        default:
            std::cout << "Property " << property << std::endl;
            throw std::invalid_argument("Property not supported");
        }
    }
    return total;
}

float get_total_energy(Particle current_particles[], int num_particles)
{
    return get_total(current_particles, num_particles, kinetic) + get_total(current_particles, num_particles, electric);
}

void get_speed_distribution(int maxwell_distribution[], int num_buckets, Particle current_particles[], int num_particles)
{
    // Choosing a static value seems to work best for visualization
    // Updating it dynamically had risks (ie., if the max speed changes due to a bug or max speed > 1000 since there are hundreds of particles)
    float max_speed = 30.;
    float min_speed = 0.;
    float speed_range = max_speed - min_speed;
    float bucket_size = speed_range / num_buckets;

    for (int i = 0; i < num_buckets; i++)
    {
        maxwell_distribution[i] = 0;
    }

    for (int i = 0; i < num_particles; i++)
    {
        int bucket = (current_particles[i].get_speed() - min_speed) / bucket_size;
        maxwell_distribution[bucket]++;
    }
}

// Also unused. Does not work for total kinetic energy = 0
// Produced graphs aren't that interesting either since the speed distribution is more informative
// void get_kinetic_energy_distribution(int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles)
// {
//     float max_energy = get_total_energy(current_particles, num_particles) / 30.;
//     float min_energy = 0.;
//     float energy_range = max_energy - min_energy;
//     float bucket_size = energy_range / num_buckets;

//     for (int i = 0; i < num_buckets; i++)
//     {
//         energy_distribution[i] = 0;
//     }

//     for (int i = 0; i < num_particles; i++)
//     {
//         int bucket = (current_particles[i].get_kinetic_energy() - min_energy) / bucket_size;
//         energy_distribution[bucket]++;
//     }
// }

// Unused
// void get_electric_potential_energy_distribution(int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles)
// {
//     float max_energy = 100.;
//     float min_energy = 0.;
//     float energy_range = max_energy - min_energy;
//     float bucket_size = energy_range / num_buckets;

//     for (int i = 0; i < num_buckets; i++)
//     {
//         energy_distribution[i] = 0;
//     }

//     for (int i = 0; i < num_particles; i++)
//     {
//         float starting_energy = 0;
//         for (int j = 0; j < num_particles; j++)
//         {
//             if (i == j)
//                 continue;

//             if (!current_particles[i].is_charged() || !current_particles[j].is_charged())
//                 continue;

//             starting_energy += current_particles[i].get_electric_potential_energy(current_particles[j]);
//         }

//         int bucket = (starting_energy - min_energy) / bucket_size;
//         energy_distribution[bucket]++;
//         // if (!current_particles[i].is_charged())
//         //     continue;

//         // float distance = (current_particles[i].position - Vec2D()).length();
//         // float electric_potential_constant = 8.99e9;
//         // float energy = electric_potential_constant * current_particles[i].charge / distance * 1e-9;
//         // int bucket = (current_particles[i].get_electric_potential_energy() - min_energy) / bucket_size;
//         // energy_distribution[bucket]++;
//     }
// }
