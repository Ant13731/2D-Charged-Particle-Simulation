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

                total += current_particles[i].get_electric_potential_energy(current_particles[j]);
            }
        }
        return total;
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

// float get_min_speed(Particle current_particles[], int num_particles)
// {
//     float min_speed = 1e9;
//     for (int i = 0; i < num_particles; i++)
//     {
//         if (std::abs(current_particles[i].velocity.length()) < min_speed)
//         {
//             min_speed = std::abs(current_particles[i].velocity.length());
//         }
//     }
//     return min_speed;
// }
// float get_max_speed(Particle current_particles[], int num_particles)
// {
//     float max_speed = -1e9;
//     for (int i = 0; i < num_particles; i++)
//     {
//         if (std::abs(current_particles[i].velocity.length()) > max_speed)
//         {
//             max_speed = std::abs(current_particles[i].velocity.length());
//         }
//     }
//     return max_speed;
// }

// float get_total_speed(Particle current_particles[], int num_particles)
// {
//     float total_speed = 0;
//     for (int i = 0; i < num_particles; i++)
//     {
//         total_speed += std::abs(current_particles[i].velocity.length());
//     }
//     return total_speed;
// }

// float get_min_kinetic_energy(Particle current_particles[], int num_particles)
// {
//     float min_energy = 1e9;
//     for (int i = 0; i < num_particles; i++)
//     {
//         float energy = 0.5 * current_particles[i].mass * std::pow(current_particles[i].velocity.length(), 2);
//         if (energy < min_energy)
//         {
//             min_energy = energy;
//         }
//     }
//     return min_energy;
// }
// float get_max_kinetic_energy(Particle current_particles[], int num_particles)
// {
//     float max_energy = -1e9;
//     for (int i = 0; i < num_particles; i++)
//     {
//         float energy = 0.5 * current_particles[i].mass * std::pow(current_particles[i].velocity.length(), 2);
//         if (energy > max_energy)
//         {
//             max_energy = energy;
//         }
//     }
//     return max_energy;
// }
// float get_total_kinetic_energy(Particle current_particles[], int num_particles)
// {
//     float total_energy = 0;
//     for (int i = 0; i < num_particles; i++)
//     {
//         total_energy += 0.5 * current_particles[i].mass * std::pow(current_particles[i].velocity.length(), 2);
//     }
//     return total_energy;
// }

// Doesnt make sense to have a min/max of these
// float get_min_electric_potential_energy(Particle current_particles[], int num_particles)
// {
//     float min_energy = 1e9;
//     for (int i = 0; i < num_particles; i++)
//     {
//         if (!current_particles[i].is_charged())
//             continue;

//         float distance = (current_particles[i].position - Vec2D()).length();
//         float electric_potential_constant = 8.99e9;
//         float energy = electric_potential_constant * current_particles[i].charge / distance;
//         if (energy < min_energy)
//         {
//             min_energy = energy;
//         }
//     }
//     return min_energy * 1e-9;
// }
// float get_max_electric_potential_energy(Particle current_particles[], int num_particles)
// {
//     float max_energy = -1e9;
//     for (int i = 0; i < num_particles; i++)
//     {
//         if (!current_particles[i].is_charged())
//             continue;

//         float distance = (current_particles[i].position - Vec2D()).length();
//         float electric_potential_constant = 8.99e9;
//         float energy = electric_potential_constant * current_particles[i].charge / distance;
//         if (energy > max_energy)
//         {
//             max_energy = energy;
//         }
//     }
//     return max_energy * 1e-9;
// }
// float get_total_electric_potential_energy(Particle current_particles[], int num_particles)
// {
//     float total_energy = 0;
//     for (int i = 0; i < num_particles; i++)
//     {
//         if (!current_particles[i].is_charged())
//             continue;

//         float distance = (current_particles[i].position - Vec2D()).length();
//         float electric_potential_constant = 8.99e9;
//         total_energy += electric_potential_constant * current_particles[i].charge / distance;
//         // total_energy += k * current_particles[i].charge * current_particles[j].charge / distance;
//     }
//     return total_energy * 1e-9;
// }

float get_total_energy(Particle current_particles[], int num_particles)
{
    return get_total(current_particles, num_particles, kinetic) + get_total(current_particles, num_particles, electric);
    // return get_total_kinetic_energy(current_particles, num_particles) + get_total_electric_potential_energy(current_particles, num_particles);
}

void get_speed_distribution(float x_axis[], int maxwell_distribution[], int num_buckets, Particle current_particles[], int num_particles)
{
    // float max_speed = get_total_speed(current_particles, num_particles) / 30.;
    // Choosing a static value seems to work best for visualization
    // Updating it dynamically had risks (ie., if the max speed changes due to a bug or max speed > 1000 since there are hundreds of particles)
    float max_speed = 30.;
    // float max_speed = get_max_speed(current_particles, num_particles);
    float min_speed = 0.;
    // float min_speed = get_min_speed(current_particles, num_particles);
    float speed_range = max_speed - min_speed;
    float bucket_size = speed_range / num_buckets;

    for (int i = 0; i < num_buckets; i++)
    {
        maxwell_distribution[i] = 0;
        x_axis[i] = min_speed + i * bucket_size;
    }

    for (int i = 0; i < num_particles; i++)
    {
        int bucket = (current_particles[i].get_speed() - min_speed) / bucket_size;
        maxwell_distribution[bucket]++;
    }
}

void get_kinetic_energy_distribution(float x_axis[], int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles)
{
    float max_energy = get_total_energy(current_particles, num_particles) / 30.;
    // float max_energy = get_max_kinetic_energy(current_particles, num_particles);
    float min_energy = 0.;
    // float min_energy = get_min_kinetic_energy(current_particles, num_particles);
    float energy_range = max_energy - min_energy;
    float bucket_size = energy_range / num_buckets;

    for (int i = 0; i < num_buckets; i++)
    {
        energy_distribution[i] = 0;
        x_axis[i] = min_energy + i * bucket_size;
    }

    for (int i = 0; i < num_particles; i++)
    {
        int bucket = (current_particles[i].get_kinetic_energy() - min_energy) / bucket_size;
        energy_distribution[bucket]++;
    }
}

void get_electric_potential_energy_distribution(float x_axis[], int energy_distribution[], int num_buckets, Particle current_particles[], int num_particles)
{
    float max_energy = 100.;
    // get_total_energy(current_particles, num_particles) / 10.;
    // float max_energy = get_max_electric_potential_energy(current_particles, num_particles);
    float min_energy = 0.;
    // float min_energy = get_min_electric_potential_energy(current_particles, num_particles);
    float energy_range = max_energy - min_energy;
    float bucket_size = energy_range / num_buckets;

    for (int i = 0; i < num_buckets; i++)
    {
        energy_distribution[i] = 0;
        x_axis[i] = min_energy + i * bucket_size;
    }

    for (int i = 0; i < num_particles; i++)
    {
        float starting_energy = 0;
        for (int j = 0; j < num_particles; j++)
        {
            if (i == j)
                continue;

            if (!current_particles[i].is_charged() || !current_particles[j].is_charged())
                continue;

            starting_energy += current_particles[i].get_electric_potential_energy(current_particles[j]);
        }

        int bucket = (starting_energy - min_energy) / bucket_size;
        energy_distribution[bucket]++;
        // if (!current_particles[i].is_charged())
        //     continue;

        // float distance = (current_particles[i].position - Vec2D()).length();
        // float electric_potential_constant = 8.99e9;
        // float energy = electric_potential_constant * current_particles[i].charge / distance * 1e-9;
        // int bucket = (current_particles[i].get_electric_potential_energy() - min_energy) / bucket_size;
        // energy_distribution[bucket]++;
    }
}
