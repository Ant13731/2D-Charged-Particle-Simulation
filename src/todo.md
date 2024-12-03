Current problems:

1. does recreating Particles in the array waste a lot of memory? If so,
   just make two arrays at the beginning and continuously update the values
   - this seems to be alright for particle count < 750 (other parts fail first)
2. particles fly away if they gain too much acceleration - should I put a cap on that?
   - reduced k constant back to 1 (by a factor of 1e-9)
3. graph not clearing properly - solved
4. If collisions happen too slowly (and particles overlap), the velocity of particles will be contributed more than once.
   This makes the particles gain a sudden burst of velocity and fly away
   - Solution: make a list of particles that have already collided with the current particle.
     Then we only allow those particles to collide again if they havent collided for more than one step
   - Solution: see if the velocity vectors are still pointing towards each other
   - Solution: dont use these equations at all - instead calculate force?
     https://gamedev.stackexchange.com/questions/32611/what-is-the-best-way-to-handle-simultaneous-collisions-in-a-physics-engine

DONE:

- measure the energy of the system over time (to make sure the charges dont go too crazy)
- measure momentum of the system over time? Difficult since it is not 1D
- plot both of those for all, uncharged, and charged particles
  -/ make graph automatically play

TODO:

- make a random particle generator that sets a certain momentum and total energy
- delta v dot delta x - if pos, moving apart already (dont collide again)
  - replace current array
- max force (softening) for charged particles - use r squared plus a constant to prevent the force from going to infinity
- electric potential energy for system, measure electric potential once per pair - sign varies (two things with opposite charges are negative) kqq/r
- energy should be conserved in both systems

  - https://physics.stackexchange.com/questions/130647/relationship-between-temperature-and-energy
  - https://courses.lumenlearning.com/suny-physics/chapter/13-3-the-ideal-gas-law/#:~:text=The%20ideal%20gas%20law%20states,T%20is%20its%20absolute%20temperature.
  - https://chem.libretexts.org/Bookshelves/Physical_and_Theoretical_Chemistry_Textbook_Maps/Supplemental_Modules_(Physical_and_Theoretical_Chemistry)/Kinetics/03%3A_Rate_Laws/3.01%3A_Gas_Phase_Kinetics/3.1.02%3A_Maxwell-Boltzmann_Distributions

Nov 20 TODO:

-/ GRAPH THE ENERGY OVER TIME - USE STD::VECTOR TO save the energy each iteration, continuously lengthening the size of the plot on pgplot (probably need to convert to an array before giving to pgplot)

- Fix wall collisions - check if already moving away from the wall, like we do with particles

Questions:

- HW6 mark is odd (24.19/30), feedback doesnt appear on avenue
- Demo not checked off on avenue
- particles dont conserve kinetic energy (sometimes slow down, speed up)
  - implemented direction check, speed no longer explodes for low numbers of particles
  - is the wall bounce equation incorrect?

<!--
- total speed of particles sometimes goes crazy for large amounts
  - 2D elastic collision equations may be the issue - is there anything like charged particles to calculate acceleration of this?
  - could have to do with how we handle multi-particle collisions - right now we just calculate the contributions pairwise and add them together -->

Questions:

- hw7 header file
- loss of energy/odd energy diagrams for charged particles
- potential + kinetic does not add up to a constant
