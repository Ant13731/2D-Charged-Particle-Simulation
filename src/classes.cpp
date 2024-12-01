#include <cmath>
#include <random>
#include <iostream>
#include <string>
#include "classes.h"

// Vector constructors and methods (standard vector operations)
Vec2D::Vec2D(float x, float y) : x(x), y(y) {}
Vec2D::Vec2D() : x(0), y(0) {}

Vec2D Vec2D::clone()
{
    return Vec2D(x, y);
}

Vec2D Vec2D::operator+(const Vec2D &v) const
{
    return Vec2D(x + v.x, y + v.y);
}
Vec2D Vec2D::operator-(const Vec2D &v) const
{
    return Vec2D(x - v.x, y - v.y);
}
Vec2D Vec2D::operator*(float s) const
{
    return Vec2D(x * s, y * s);
}
Vec2D Vec2D::operator/(float s) const
{
    return Vec2D(x / s, y / s);
}
Vec2D Vec2D::operator+=(const Vec2D &v)
{
    x += v.x;
    y += v.y;
    return *this;
}

float Vec2D::dot(const Vec2D &v) const
{
    return x * v.x + y * v.y;
}
float Vec2D::length() const
{
    return std::sqrt(x * x + y * y);
}
Vec2D Vec2D::perpendicular() const
{
    return Vec2D(-y, x);
}
Vec2D Vec2D::normalize() const
{
    return *this / length();
}
void Vec2D::zero()
{
    x = 0;
    y = 0;
}

// Particle constructors and methods
Particle::Particle(Vec2D position, Vec2D velocity, Vec2D acceleration, float mass, float charge, float radius)
    : position(position), velocity(velocity), acceleration(acceleration), mass(mass), charge(charge), radius(radius) {}
Particle::Particle(Vec2D position, Vec2D velocity, float mass, float charge, float radius)
    : position(position), velocity(velocity), acceleration(Vec2D()), mass(mass), charge(charge), radius(radius) {}
Particle::Particle()
    : position(Vec2D()), velocity(Vec2D()), acceleration(Vec2D()), mass(0), charge(0), radius(0.25) {}

Particle Particle::clone()
{
    return Particle(position, velocity, acceleration, mass, charge, radius);
}

bool Particle::particles_collided(Particle &other)
{
    float collision_radius = radius + other.radius;
    return (position - other.position).length() < collision_radius;
    // return (position - other.position).length() < 0.1;
}
bool Particle::is_moving_apart(Particle &other)
{
    return (velocity - other.velocity).dot(position - other.position) > 0;
}

Vec2D Particle::get_velocity_contributions(Particle &other)
{
    if (!particles_collided(other) || is_moving_apart(other))
    {
        return Vec2D();
    }

    // 2D elastic collision
    float mass_coefficient = (other.mass * 2) / (other.mass + mass);
    float inner_product = (velocity - other.velocity).dot(position - other.position);
    float distance = std::pow((position - other.position).length(), 2);
    float velocity_coefficient = inner_product / distance;

    return (other.position - position) * mass_coefficient * velocity_coefficient;
}

Vec2D Particle::get_acceleration_contributions(Particle &other)
{
    // Acceleration can only be applied if both particles are charged
    if (!is_charged() || !other.is_charged())
    {
        return Vec2D();
    }

    float distance = std::pow((position - other.position).length(), 2.) + acceleration_epsilon;
    return (position - other.position) * k * charge * other.charge / (distance * mass);
}
bool Particle::is_charged() { return !(charge < 0.000001 && charge > -0.000001); }

float Particle::get_speed() { return std::abs(velocity.length()); }
float Particle::get_kinetic_energy() { return 0.5 * mass * std::pow(get_speed(), 2); }
float Particle::get_electric_potential_energy(Particle &other)
{
    if (!is_charged() || !other.is_charged())
    {
        return 0;
    }

    float distance = std::pow((position - other.position).length(), 1.) + acceleration_epsilon;
    return k * charge * other.charge / distance;
}

Particle Particle::make_rand_particle(float sqr_bounds)
{
    // Randomly generate a particle within the bounds of the container
    // Velocity is bounded by container size too
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-sqr_bounds / 1.05, sqr_bounds / 1.05);

    Vec2D position = Vec2D(dist(mt), dist(mt));
    Vec2D velocity = Vec2D(dist(mt), dist(mt));
    // float mass = std::abs(dist(mt));
    float mass = 1.;

    return Particle(position, velocity, mass, 0.f, 0.25);
}
Particle Particle::make_rand_charged_particle(float sqr_bounds)
{
    // Same as above but with a charge
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-sqr_bounds / 1.05, sqr_bounds / 1.05);

    Vec2D position = Vec2D(dist(mt), dist(mt));
    Vec2D velocity = Vec2D(dist(mt), dist(mt));
    float mass = 1.;
    // float mass = std::abs(dist(mt));
    // Vec2D acceleration = Vec2D(dist(mt), dist(mt)); // TODO remove? make 0?
    Vec2D acceleration = Vec2D();

    float x = dist(mt);
    float charge = (x >= 0) ? 1. : -1.;
    // float charge = dist(mt);

    return Particle(position, velocity, acceleration, mass, charge, 0.25);
}
std::string Particle::to_string()
{
    // For debugging
    return "Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")\n" +
           "Velocity: (" + std::to_string(velocity.x) + ", " + std::to_string(velocity.y) + ")\n" +
           "Acceleration: (" + std::to_string(acceleration.x) + ", " + std::to_string(acceleration.y) + ")\n" +
           "Mass: " + std::to_string(mass) + "\n" +
           "Charge: " + std::to_string(charge) + "\n";
}

// Bounding box constructor/methods
RectangleContainer::RectangleContainer(float left, float right, float top, float bottom) : left(left), right(right), top(top), bottom(bottom) {}

bool RectangleContainer::is_in_bounds(Vec2D position)
{
    return position.x >= left && position.x <= right && position.y >= bottom && position.y <= top;
}

Vec2D RectangleContainer::get_closest_in_bounds_normal(Vec2D position)
{
    // Reflect vector if out of bounds - unused in favour of simpler checks below
    Vec2D normal = Vec2D();
    if (position.x < left)
    {
        normal.x = 1;
    }
    else if (position.x > right)
    {
        normal.x = -1;
    }
    if (position.y < bottom)
    {
        normal.y = 1;
    }
    else if (position.y > top)
    {
        normal.y = -1;
    }
    return normal.normalize();
}

Vec2D RectangleContainer::get_collision_velocity(Particle &particle)
{
    Vec2D new_velocity = particle.velocity.clone();
    if (is_in_bounds(particle.position))
    {
        return new_velocity;
    }

    // Reflect velocity vectors if out of bounds
    // Vec2D normal = get_closest_in_bounds_normal(particle.position);
    // src: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    // particle.velocity = particle.velocity - (normal * 2 * particle.velocity.dot(normal));
    if (particle.position.x < left || particle.position.x > right)
    {
        new_velocity.x = -particle.velocity.x;
    }
    if (particle.position.y < bottom || particle.position.y > top)
    {
        new_velocity.y = -particle.velocity.y;
    }
    return new_velocity;
}
