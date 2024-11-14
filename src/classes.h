#pragma once
#include <string>

class Vec2D
{
public:
    float x;
    float y;

    Vec2D(float x, float y);
    Vec2D();
    Vec2D clone();

    Vec2D operator+(const Vec2D &v) const;
    Vec2D operator-(const Vec2D &v) const;
    Vec2D operator*(float s) const;
    Vec2D operator/(float s) const;
    Vec2D operator+=(const Vec2D &v);
    float dot(const Vec2D &v) const;
    float length() const;
    Vec2D perpendicular() const;
    Vec2D normalize() const;
};

class Particle
{
public:
    Vec2D position;
    Vec2D velocity;
    Vec2D acceleration;
    float mass;
    float charge;

    Particle(Vec2D position, Vec2D velocity, float mass, float charge);
    Particle(Vec2D position, Vec2D velocity, Vec2D acceleration, float mass, float charge);

    Particle();
    static Particle make_rand_particle(float sqr_bounds);
    static Particle make_rand_charged_particle(float sqr_bounds);
    Particle clone();

    bool particles_collided(Particle &other);
    bool particles_facing_each_other(Particle &other);
    Vec2D get_velocity_contributions(Particle &other);
    Vec2D get_acceleration_contributions(Particle &other);
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
