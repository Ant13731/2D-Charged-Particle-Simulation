#include "ode.h"
#include "classes.h"

// float get_next_position(float x_i, float v_i_half, float dt)
// {
//     return x_i + v_i_half * dt;
// }

// float get_next_half_velocity(float v_i, float a_i, float dt)
// {
//     return v_i + 0.5 * a_i * dt;
// }

Vec2D get_next_half_velocity(Vec2D v_i, Vec2D a_i, float dt)
{
    return v_i + a_i * 0.5 * dt;
}

Vec2D get_next_position(Vec2D x_i, Vec2D v_i_half, float dt)
{
    return x_i + v_i_half * dt;
}

// float get_next_acceleration(float force, float mass)
// {
//     return force / mass;
// }