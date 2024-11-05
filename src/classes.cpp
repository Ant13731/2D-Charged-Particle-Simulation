#include <cmath>
#include <random>
#include "classes.h"

class Vec2D
{
public:
    float x;
    float y;

    Vec2D(float x, float y) : x(x), y(y) {}
    Vec2D() : x(0), y(0) {}

    Vec2D clone()
    {
        return Vec2D(x, y);
    }

    Vec2D operator+(const Vec2D &v) const
    {
        return Vec2D(x + v.x, y + v.y);
    }
    Vec2D operator-(const Vec2D &v) const
    {
        return Vec2D(x - v.x, y - v.y);
    }
    Vec2D operator*(float s) const
    {
        return Vec2D(x * s, y * s);
    }
    Vec2D operator/(float s) const
    {
        return Vec2D(x / s, y / s);
    }
    Vec2D operator+=(const Vec2D &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    float dot(const Vec2D &v) const
    {
        return x * v.x + y * v.y;
    }
    // float cross(const Vec2D &v) const
    // {
    //     return x * v.y - y * v.x;
    // }
    float length() const
    {
        return std::sqrt(x * x + y * y);
    }
    Vec2D perpendicular() const
    {
        return Vec2D(-y, x);
    }
    Vec2D normalize() const
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
};

class Particle
{
public:
    Vec2D position;
    Vec2D velocity;
    float mass;
    Vec2D acceleration = 0;

    Particle(Vec2D position, Vec2D velocity, float mass) : position(position), velocity(velocity), mass(mass) {}
    Particle() : position(Vec2D()), velocity(Vec2D()), mass(0) {}
    Particle clone()
    {
        return Particle(position.clone(), velocity.clone(), mass);
    }

    bool particles_collided(Particle &other)
    {
        return (position - other.position).length() < 0.01;
    }
    bool is_charged() { return false; }

    // void update_velocity(Particle &other)
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

    Vec2D get_velocity_contributions(Particle &other)
    {
        if (!particles_collided(other))
        {
            return Vec2D();
        }

        float mass_coefficient = (other.mass * 2) / (other.mass + mass);
        float inner_product = (velocity - other.velocity).dot(position - other.position);
        float distance = std::pow((position - other.position).length(), 2);
        float velocity_coefficient = inner_product / distance;

        return mass_coefficient * velocity_coefficient * (position - other.position);
    }
};

Particle Particle::make_rand_particle(float sqr_bounds)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-sqr_bounds / 2., sqr_bounds / 2.);

    Vec2D position = Vec2D(dist(mt), dist(mt));
    Vec2D velocity = Vec2D(dist(mt), dist(mt));
    float mass = dist(mt);

    return Particle(position, velocity, mass);
}

class ChargedParticle : public Particle
{
public:
    float charge;

    ChargedParticle(Vec2D position, Vec2D velocity, float mass, Vec2D acceleration, float charge) : Particle(position, velocity, mass), acceleration(Vec2D), charge(0) {}
    ChargedParticle() : Particle(), acceleration(Vec2D()), charge(0) {}

    ChargedParticle clone()
    {
        return ChargedParticle(position.clone(), velocity.clone(), mass, acceleration.clone(), charge);
    }

    Vec2D get_acceleration_contributions(Particle &other)
    {
        return Vec2D();
    }

    Vec2D get_acceleration_contributions(ChargedParticle &other)
    {
        float distance = std::pow((position - other.position).length(), 2);
        float k = 8.99 * std::pow(10, 9);
        return k * charge * other.charge / (distance * mass) * (position - other.position);
    }
    bool is_charged() { return true; }

    // void update_acceleration(ChargedParticle &other)
    // {
    //     float distance = std::pow((position - other.position).length(), 2);
    //     float k = 8.99 * std::pow(10, 9);
    //     float acceleration_coefficient = k * charge * other.charge / (distance * mass);
    //     acceleration = acceleration + acceleration_coefficient * (position - other.position);
    // }
};

ChargedParticle ChargedParticle::make_rand_particle(float sqr_bounds)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-sqr_bounds / 2., sqr_bounds / 2.);

    Vec2D position = Vec2D(dist(mt), dist(mt));
    Vec2D velocity = Vec2D(dist(mt), dist(mt));
    float mass = dist(mt);
    Vec2D acceleration = Vec2D(dist(mt), dist(mt));
    float charge = dist(mt);

    return ChargedParticle(position, velocity, mass, acceleration, charge);
}

class RectangleContainer : public Container
{
public:
    float left;
    float right;
    float top;
    float bottom;

    bool is_in_bounds(Vec2D position)
    {
        return posision.x >= left && position.x <= right && position.y >= bottom && position.y <= top;
    }

    Vec2D get_closest_in_bounds_normal(Vec2D position)
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
        return normal;
    }

    void handle_collision(Particle &particle)
    {
        if (is_in_bounds(particle.position))
        {
            return;
        }

        Vec2D normal = get_closest_in_bounds_normal(particle.position);
        // src: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
        particle.velocity = particle.velocity - normal.normalize() * 2 * particle.velocity.dot(normal);
    }
};
