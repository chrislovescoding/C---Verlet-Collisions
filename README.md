# CPP-SFML-Verlet-Collisions


## Introduction

Although this is my first repo, I have been coding for a long time now. I have countless projects and will upload these projects onto my account.

I was inspired by [Pezzza's work youtube channel](https://www.youtube.com/@PezzzasWork)

This code is a c++ SFML integration of verlet physics solving. I have done this project in p5js so this is my version using C++ trying to use as many best practices as possible (if you spot something I should change please tell me as I want to learn C++ from the start using best practices).

## Features

- Particles with realistic Verlet integration for motion.
- Collision detection and resolution among particles.
- Ability to dynamically add particles by clicking within the window.
- Randomised starting positions and colors for particles.
- Constraints to ensure particles stay within the window's bounds.
- Substeps which allow to maintain a stable simulation as the number of particles increases

## How to Use

1. Install dependencies (install SFML on your machine, follow the instructions on the [official website](https://www.sfml-dev.org/download.php)).
2. Modify or remove the .vscode folder and tailor it to your system
3. Compile and run the project.
4. Enter the desired number of particles at the start.
5. Watch as the particles move, collide, and react to gravity.
6. Add more particles by clicking anywhere within the window. The number of particles will be displayed in the console.

## Code Structure

- **main.cpp**:
    - Contains the main logic, including the SFML game loop, collision detection, and particle updates.
    - Handles user input to add more particles to the simulation.
    
- **Particle.hpp / Particle.cpp**:
    - Defines the `Particle` class, which represents an individual particle in the simulation.
    - Handles particle motion, acceleration, and display.
    - Contains methods to constrain particles within the window's bounds and update their positions using Verlet integration.

## Dependencies

- [SFML](https://www.sfml-dev.org/): Used for graphics, window management, and user input.

## Future Enhancements

- Add more interactivity, like adjusting gravity or particle properties in real-time.
- Implement advanced collision resolution techniques for a more realistic simulation.
- Optimise my code by implementing a quadtree to allow for more particles to be simulated whilst maintaining a high frame rate.

