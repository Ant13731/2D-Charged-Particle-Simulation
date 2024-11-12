#include <cmath>
#include <random>
#include <iostream>
#include <string>
#include "classes.h"

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
// float cross(const Vec2D &v) const
// {
//     return x * v.y - y * v.x;
// }
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
// Vec2D rotate(float angle) const
// {
//     float c = cos(angle);
//     float s = sin(angle);
//     return Vec2D(x * c - y * s, x * s + y * c);
// }
// Vec2D reflect(const Vec2D &normal) const
// {
//     return *this - normal * 2 * dot(normal);
// }
// Vec2D project(const Vec2D &v) const
// {
//     return v * dot(v) / v.dot(v);
// }
// Vec2D projectOntoUnit(const Vec2D &v) const
// {
//     return v * dot(v);
// }

Particle::Particle(Vec2D position, Vec2D velocity, Vec2D acceleration, float mass, float charge)
    : position(position), velocity(velocity), acceleration(acceleration), mass(mass), charge(charge) {}
Particle::Particle(Vec2D position, Vec2D velocity, float mass, float charge)
    : position(position), velocity(velocity), acceleration(Vec2D()), mass(mass), charge(charge) {}
Particle::Particle()
    : position(Vec2D()), velocity(Vec2D()), acceleration(Vec2D()), mass(0), charge(0) {}

Particle Particle::clone()
{
    return Particle(position, velocity, acceleration, mass, charge);
}

bool Particle::particles_collided(Particle &other)
{
    // std::cout << "Particles " << (position - other.position).length() << " apart\n";

    return (position - other.position).length() < 0.5;
    // return (position - other.position).length() < 0.1;
}

bool Particle::particles_facing_each_other(Particle &other)
{
    return (velocity - other.velocity).dot(position - other.position) < 0;
}

// void Particle::update_velocity(Particle &other)
// {
//     if (!particles_collided(other))
//     {
//         return;
//     }

//     float mass_coefficient = (other.mass * 2) / (other.mass + mass);
//     float inner_product = (velocity - other.velocity).dot(position - other.position);
//     float distance = std::pow((position - other.position).length(), 2);
//     float velocity_coefficient = inner_product / distance;

//     velocity = velocity - mass_coefficient * velocity_coefficient * (position - other.position);
// }
// void update_acceleration(Particle &other) {}

Vec2D Particle::get_velocity_contributions(Particle &other)
{
    if (!particles_collided(other))
    {
        return Vec2D();
    }

    std::cout << "Particles collided\n";

    float mass_coefficient = (other.mass * 2) / (other.mass + mass);
    float inner_product = (velocity - other.velocity).dot(position - other.position);
    float distance = std::pow((position - other.position).length(), 2);
    float velocity_coefficient = inner_product / distance;

    return (other.position - position) * mass_coefficient * velocity_coefficient;
}

Vec2D Particle::get_acceleration_contributions(Particle &other)
{
    if (!is_charged() || !other.is_charged())
    {
        return Vec2D();
    }
    float distance = std::pow((position - other.position).length(), 2);
    float k = 8.99e9;
    return (position - other.position) * k * charge * other.charge / (distance * mass) * 1e-9;
}
bool Particle::is_charged() { return !(charge < 0.000001 && charge > -0.000001); }

// void ChargedParticle::update_acceleration(ChargedParticle &other)
// {
//     float distance = std::pow((position - other.position).length(), 2);
//     float k = 8.99 * std::pow(10, 9);
//     float acceleration_coefficient = k * charge * other.charge / (distance * mass);
//     acceleration = acceleration + acceleration_coefficient * (position - other.position);
// }

Particle Particle::make_rand_particle(float sqr_bounds)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-sqr_bounds / 2., sqr_bounds / 2.);

    Vec2D position = Vec2D(dist(mt), dist(mt));
    Vec2D velocity = Vec2D(dist(mt), dist(mt));
    // float mass = std::abs(dist(mt));
    float mass = 1.;

    return Particle(position, velocity, mass, 0.f);
}
Particle Particle::make_rand_charged_particle(float sqr_bounds)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-sqr_bounds / 2., sqr_bounds / 2.);

    Vec2D position = Vec2D(dist(mt), dist(mt));
    Vec2D velocity = Vec2D(dist(mt), dist(mt));
    float mass = 1.;
    // float mass = std::abs(dist(mt));
    // Vec2D acceleration = Vec2D(dist(mt), dist(mt)); // TODO remove? make 0?
    Vec2D acceleration = Vec2D();

    float x = dist(mt);
    float charge = (x >= 0) ? 1. : -1.;
    // float charge = dist(mt);

    return Particle(position, velocity, acceleration, mass, charge);
}
std::string Particle::to_string()
{
    return "Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")\n" +
           "Velocity: (" + std::to_string(velocity.x) + ", " + std::to_string(velocity.y) + ")\n" +
           "Acceleration: (" + std::to_string(acceleration.x) + ", " + std::to_string(acceleration.y) + ")\n" +
           "Mass: " + std::to_string(mass) + "\n" +
           "Charge: " + std::to_string(charge) + "\n";
}

RectangleContainer::RectangleContainer(float left, float right, float top, float bottom) : left(left), right(right), top(top), bottom(bottom) {}

bool RectangleContainer::is_in_bounds(Vec2D position)
{
    return position.x >= left && position.x <= right && position.y >= bottom && position.y <= top;
}

Vec2D RectangleContainer::get_closest_in_bounds_normal(Vec2D position)
{
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
