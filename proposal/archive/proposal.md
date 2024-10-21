# DATASCI 2G03 Project Proposal

## Elastic Collisions between Contained Particles

<!-- TODO ask prof if these equations are enough, he mentioned each particle needs 6 equations? -->

## Introduction

Simple 2D video games like pong, brick breaker, or even 8 ball pool have a great deal of both physical and computational concerns. In particular, this project aims to simulate the motion of moving particles and the collision interactions between them.

<!-- This project aims to simulate the motion of moving charged particles and interactions between them. -->

The main problems we will be solving are:

- Motion of several (round) particles with parametric starting configurations
- Elastic collisions between particles and a bounding box

The first part of this project will consist of modelling the interaction between many particles in a containing box the hopes of achieving a 2D Maxwell–Boltzmann distribution of velocities. Then, we will extend these interactions with the addition of charged particles to simulate non-constant acceleration.

## Equations

The ODEs and other equations used to simulate this problem are listed below. The goal of this simulation is to track the position of objects (represented by $s$) over some length of time $t$. Each particle will have some mass $m$ and starting velocity $v$.

Velocity ($v$) of one particle:
$$v = \frac{ds}{dt}$$

Acceleration ($a$) of one particle:
$$a = \frac{dv}{dt} = \frac{d^2s}{dt^2}$$

Momentum of one particle:
$$p = mv$$

Kinetic energy of one particle:
$$E = \frac{1}{2}mv^2$$

Newton's second law:
$$F = ma$$

<!-- Net force on a particle (for when particles collide):
$$F_{net} = \frac{dp}{dt}$$

Relationship between force and acceleration, used for the Normal force in collisions:
$$F = ma$$ -->

<!-- Coulomb's law: Force of charged particles against one another:
$$F_{charge} = \frac{kq_1q_2}{r^2}$$ -->

<!-- Acceleration due to gravity:
$$a_g = 9.8 \frac{\text{m}}{\text{s}^2}$$ -->

<!-- Consider below for part 2? -->

<!-- Force of air resistance (or any force dependent on the velocity of the object). Let $c$ be some positive coefficient of this friction:
$$F_{air} = -cv$$ -->

<!-- Thus, the equation of motion for our particle (without collisions) can be written as: -->

<!-- $$m\frac{dv}{dt} = ma_g + a_{air}$$ -->

The below equations are concerned with calculating the vectors of velocity resulting from an elastic collision. Let $v_1$ represent the first particle's velocity and $v_2$ for the second particle's velocity. Additionally, let $v'$ represent the velocity after the collision and $v$ for the velocities prior to the collision.

$$
\begin{aligned}
\mathbf {v} '_{1}&=\mathbf {v} _{1}-{\frac {2m*{2}}{m*{1}+m*{2}}}\ {\frac {\langle \mathbf {v} *{1}-\mathbf {v} _{2},\,\mathbf {x} _{1}-\mathbf {x} _{2}\rangle }{\|\mathbf {x} _{1}-\mathbf {x} _{2}\|^{2}}}\ (\mathbf {x} _{1}-\mathbf {x} _{2})\\
\mathbf {v} '_{2}&=\mathbf {v} _{2}-{\frac {2m_{1}}{m*{1}+m*{2}}}\ {\frac {\langle \mathbf {v} _{2}-\mathbf {v} _{1},\,\mathbf {x} _{2}-\mathbf {x} _{1}\rangle }{\|\mathbf {x} _{2}-\mathbf {x} _{1}\|^{2}}}\ (\mathbf {x} _{2}-\mathbf {x} _{1})
\end{aligned}
$$

Coulomb's law: Force of charged particles against one another:
$$F_{charge} = \frac{kq_1q_2}{r^2}$$

## Configuration Parameters

- Starting position $s$ of each particle
- Initial velocity $v$ of each particle
- Mass $m$ of each particle
- Radius of each particle $r$
- Charge of different particles $q$
<!-- - Object deformation time $t$ when particles collide (assume elastic collisions) -->

<!-- #### Ideas
- maybe split off a chunk of each particle that collides
  - start with 2, take off % amount of each particle in a collision to create a new particle
  - recursive particle generation?
- add a new type of particle for inelastic collisions (ie. two particles become one particle) and continue with the same momentum as before
- is there any simple visualization/graphing libraries? Maybe we could use a terminal to render movement of the particles?

---

- Inelastic collapse - coefficient of restitution is too small
- https://en.wikipedia.org/wiki/Maxwell%E2%80%93Boltzmann_distribution - start with some fast particles, some slow particles, they should even out to this distribution
- eg. electric fields as acceleration or smth -->

## Interesting Properties

- number of times a particle is hit before stopping the simulation
- speed of particles over time (momentum of all particles should remain constant)
- position of particles on a graph
- distribution of particle speeds (Maxwell–Boltzmann distribution)
- unique path of each particle

## References

- Equations of motion: https://en.wikipedia.org/wiki/Equations_of_motion
- Elastic collisions: https://en.wikipedia.org/wiki/Elastic_collision
- Maxwell–Boltzmann distribution: https://en.wikipedia.org/wiki/Maxwell%E2%80%93Boltzmann_distribution
  <!-- - Air resistance: https://farside.ph.utexas.edu/teaching/336k/Newton/node29.html -->
