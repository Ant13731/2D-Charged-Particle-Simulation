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

    Particle(Vec2D position, Vec2D velocity, float mass);
    Particle();
    static Particle make_rand_particle(float sqr_bounds);
    Particle clone();

    bool particles_collided(Particle &other);
    Vec2D get_velocity_contributions(Particle &other);
    bool is_charged();
};

class ChargedParticle : public Particle
{
public:
    float charge;

    ChargedParticle(Vec2D position, Vec2D velocity, float mass, Vec2D acceleration, float charge);
    ChargedParticle();
    static ChargedParticle make_rand_particle(float sqr_bounds);
    ChargedParticle clone();

    Vec2D get_acceleration_contributions(Particle &other);
    Vec2D get_acceleration_contributions(ChargedParticle &other);
};

class Container
{
public:
    virtual bool is_in_bounds(Vec2D position) = 0;
    virtual Vec2D get_closest_in_bounds_normal(Vec2D position) = 0;
    virtual void handle_collision(Particle &particle) = 0;
};

class RectangleContainer : public Container
{
public:
    float left;
    float right;
    float top;
    float bottom;
    bool is_in_bounds(Vec2D position);
    Vec2D get_closest_in_bounds_normal(Vec2D position);
    void handle_collision(Particle &particle);
};
