#pragma once

#include "classes.h"

Vec2D get_next_half_velocity(Vec2D v_i, Vec2D a_i, float dt);
Vec2D get_next_position(Vec2D x_i, Vec2D v_i_half, float dt);