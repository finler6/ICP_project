# 2D Mobile Robot Simulator

## Description

This project is a simple 2D simulator for mobile robots operating within a bounded rectangular environment. Users can interactively place multiple robots and static obstacles, configure their properties, and observe their behavior through a graphical user interface (GUI). The simulation state, including robot and obstacle placements and parameters, can be saved to and loaded from human-readable text files.

The simulator supports two types of robots:
1.  **Autonomous Robots:** Navigate the environment in a straight line, automatically avoiding detected obstacles by turning a predefined angle.
2.  **Remote-Controlled Robots:** Can be controlled by the user via keyboard commands (move forward, rotate left/right). They stop moving forward upon detecting an obstacle.

The simulation employs simplified physics based on discrete time steps, continuous 2D space, constant velocity, and constant angular velocity, disregarding factors like mass or inertia.

## Features

* **GUI:** Visualizes the simulation environment, robots, and obstacles using the Qt framework.
* **Interactive Environment Setup:** Add, remove, and edit robots and obstacles directly via context menus in the GUI.
* **Configuration Management:**
    * Save the current simulation setup (robots and obstacles) to a text file.
    * Load simulation setups from existing configuration files.
* **Robot Types:**
    * Autonomous robots with sensor-based obstacle avoidance.
    * Remote-controlled robots responsive to keyboard input.
* **Simulation Control:** Start, pause, resume, and stop the simulation via GUI controls.
* **Collision Detection:** Basic collision detection between robots, obstacles, and environment boundaries.
* **Documentation:** Source code documented using Doxygen-style comments.

## Tech Stack

* **Language:** C++17
* **GUI Toolkit:** Qt Framework (Version 5.5 or higher recommended)

## Prerequisites

* C++17 compatible compiler (e.g., GCC, Clang)
* Make build automation tool
* Qt5 development libraries (ensure `qmake` is in your PATH)

## Build Instructions

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/finler6/robot_Simulator robot/
    cd robot/
    ```
2.  **Compile the project:** Navigate to the project's root directory (where the `Makefile` should be located) and run:
    ```bash
    make
    ```
    This command should compile the source code and create the executable file.

## Running the Simulator

After successful compilation, run the simulator using:

```bash
make run
