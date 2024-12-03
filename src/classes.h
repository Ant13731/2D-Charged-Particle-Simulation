#pragma once
#include <string>

// Representation of a 2D vector
class Vec2D
{
public:
    // horizontal component
    float x;
    // vertical component
    float y;

    Vec2D(float x, float y);
    Vec2D();
    // Create a copy of the vector
    Vec2D clone();

    Vec2D operator+(const Vec2D &v) const;
    Vec2D operator-(const Vec2D &v) const;
    Vec2D operator*(float s) const;
    Vec2D operator/(float s) const;
    Vec2D operator+=(const Vec2D &v);
    // Dot product
    float dot(const Vec2D &v) const;
    float length() const;
    Vec2D perpendicular() const;
    Vec2D normalize() const;
    void zero();
};

// Representation of a particle
class Particle
{
public:
    Vec2D position;
    Vec2D velocity;
    Vec2D acceleration;
    float mass;
    float charge;

    float radius; // Used for collision detection
    static constexpr float k = 5;
    static constexpr float acceleration_epsilon = 1e-1;

    Particle(Vec2D position, Vec2D velocity, float mass, float charge, float radius);
    Particle(Vec2D position, Vec2D velocity, Vec2D acceleration, float mass, float charge, float radius);
    Particle();

    // Make a random particle between the square bounds
    static Particle make_rand_particle(float sqr_bounds);
    // Make a random charged particle between the square bounds
    static Particle make_rand_charged_particle(float sqr_bounds);
    // Create a copy of the vector
    Particle clone();

    // Check if two particles have collided
    bool particles_collided(Particle &other);
    // Check if two particles are moving apart
    bool is_moving_apart(Particle &other);

    float get_speed();
    float get_kinetic_energy();
    float get_electric_potential_energy(Particle &other);

    // Get resulting velocity of this particle from a collision with another particle
    Vec2D get_velocity_contributions(Particle &other);
    // Get resulting acceleration of this (charged) particle from another (charged) particle
    Vec2D get_acceleration_contributions(Particle &other);
    // Check if the particle is charged
    bool is_charged();
    std::string to_string();
};

class Container
{
public:
    virtual bool is_in_bounds(Vec2D position) = 0;
    virtual Vec2D get_closest_in_bounds_normal(Vec2D position) = 0;
    virtual Vec2D get_collision_velocity(Particle &particle) = 0;
};

class RectangleContainer : public Container
{
public:
    float left;
    float right;
    float top;
    float bottom;
    RectangleContainer(float left, float right, float top, float bottom);
    bool is_in_bounds(Vec2D position);
    Vec2D get_closest_in_bounds_normal(Vec2D position);
    Vec2D get_collision_velocity(Particle &particle);
};
