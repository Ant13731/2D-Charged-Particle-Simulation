#include "classes.h"
#include "aggregates.h"
#include <cmath>

float get_min_speed(Particle current_particles[], int num_particles)
{
    float min_speed = INFINITY;
    for (int i = 0; i < num_particles; i++)
    {
        if (current_particles[i].velocity.length() < min_speed)
        {
            min_speed = current_particles[i].velocity.length();
        }
    }
    return min_speed;
}
float get_max_speed(Particle current_particles[], int num_particles)
{
    float max_speed = -INFINITY;
    for (int i = 0; i < num_particles; i++)
    {
        if (current_particles[i].velocity.length() > max_speed)
        {
            max_speed = current_particles[i].velocity.length();
        }
    }
    return max_speed;
}
float get_total_speed(Particle current_particles[], int num_particles)
{
    float total_speed = 0;
    for (int i = 0; i < num_particles; i++)
    {
        total_speed += current_particles[i].velocity.length();
    }
    return total_speed;
}

float get_min_kinetic_energy(Particle current_particles[], int num_particles)
{
    float min_energy = INFINITY;
    for (int i = 0; i < num_particles; i++)
    {
        float energy = 0.5 * current_particles[i].mass * std::pow(current_particles[i].velocity.length(), 2);
        if (energy < min_energy)
        {
            min_energy = energy;
        }
    }
    return min_energy;
}
float get_max_kinetic_energy(Particle current_particles[], int num_particles)
{
    float max_energy = -INFINITY;
    for (int i = 0; i < num_particles; i++)
    {
        float energy = 0.5 * current_particles[i].mass * std::pow(current_particles[i].velocity.length(), 2);
        if (energy > max_energy)
        {
            max_energy = energy;
        }
    }
    return max_energy;
}
float get_total_kinetic_energy(Particle current_particles[], int num_particles)
{
    float total_energy = 0;
    for (int i = 0; i < num_particles; i++)
    {
        total_energy += 0.5 * current_particles[i].mass * std::pow(current_particles[i].velocity.length(), 2);
    }
    return total_energy;
}

float get_min_electric_potential_energy(Particle current_particles[], int num_particles)
{
    float min_energy = INFINITY;
    for (int i = 0; i < num_particles; i++)
    {
        if (!current_particles[i].is_charged())
            continue;

        float distance = (current_particles[i].position - Vec2D()).length();
        float electric_potential_constant = 8.99e9;
        float energy = electric_potential_constant * current_particles[i].charge / distance;
        if (energy < min_energy)
        {
            min_energy = energy;
        }
    }
    return min_energy * 1e-9;
}
float get_max_electric_potential_energy(Particle current_particles[], int num_particles)
{
    float max_energy = -INFINITY;
    for (int i = 0; i < num_particles; i++)
    {
        if (!current_particles[i].is_charged())
            continue;

        float distance = (current_particles[i].position - Vec2D()).length();
        float electric_potential_constant = 8.99e9;
        float energy = electric_potential_constant * current_particles[i].charge / distance;
        if (energy > max_energy)
        {
            max_energy = energy;
        }
    }
    return max_energy * 1e-9;
}
float get_total_electric_potential_energy(Particle current_particles[], int num_particles)
{
    float total_energy = 0;
    for (int i = 0; i < num_particles; i++)
    {
        if (!current_particles[i].is_charged())
            continue;

        float distance = (current_particles[i].position - Vec2D()).length();
        float electric_potential_constant = 8.99e9;
        total_energy += electric_potential_constant * current_particles[i].charge / distance;
        // total_energy += k * current_particles[i].charge * current_particles[j].charge / distance;
    }
    return total_energy * 1e-9;
}

float get_total_energy(Particle current_particles[], int num_particles)
{
    return get_total_kinetic_energy(current_particles, num_particles) + get_total_electric_potential_energy(current_particles, num_particles);
}

void get_speed_distribution(float x_axis[], float maxwell_distribution[], int num_buckets, Particle current_particles[], int num_particles)
{
    float max_speed = get_max_speed(current_particles, num_particles);
    float min_speed = get_min_speed(current_particles, num_particles);
    float speed_range = max_speed - min_speed;
    float bucket_size = speed_range / num_buckets;

    for (int i = 0; i < num_particles; i++)
    {
        int bucket = (current_particles[i].velocity.length() - min_speed) / bucket_size;
        maxwell_distribution[bucket]++;
        x_axis[bucket] = min_speed + bucket * bucket_size;
    }
}

void get_kinetic_energy_distribution(float x_axis[], float energy_distribution[], int num_buckets, Particle current_particles[], int num_particles)
{
    float max_energy = get_max_kinetic_energy(current_particles, num_particles);
    float min_energy = get_min_kinetic_energy(current_particles, num_particles);
    float energy_range = max_energy - min_energy;
    float bucket_size = energy_range / num_buckets;

    for (int i = 0; i < num_particles; i++)
    {
        float energy = 0.5 * current_particles[i].mass * std::pow(current_particles[i].velocity.length(), 2);
        int bucket = (energy - min_energy) / bucket_size;
        energy_distribution[bucket]++;
        x_axis[bucket] = min_energy + bucket * bucket_size;
    }
}

void get_electric_potential_energy_distribution(float x_axis[], float energy_distribution[], int num_buckets, Particle current_particles[], int num_particles)
{
    float max_energy = get_max_electric_potential_energy(current_particles, num_particles);
    float min_energy = get_min_electric_potential_energy(current_particles, num_particles);
    float energy_range = max_energy - min_energy;
    float bucket_size = energy_range / num_buckets;

    for (int i = 0; i < num_particles; i++)
    {
        if (!current_particles[i].is_charged())
            continue;

        float distance = (current_particles[i].position - Vec2D()).length();
        float electric_potential_constant = 8.99e9;
        float energy = electric_potential_constant * current_particles[i].charge / distance * 1e-9;
        int bucket = (energy - min_energy) / bucket_size;
        energy_distribution[bucket]++;
        x_axis[bucket] = min_energy + bucket * bucket_size;
    }
}
