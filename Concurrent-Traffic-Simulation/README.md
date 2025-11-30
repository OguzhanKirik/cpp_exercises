# CPPND: Program a Concurrent Traffic Simulation

<img src="data/traffic_simulation.gif"/>

# 🚦 Concurrency Project — Traffic Simulation

This project simulates **vehicle traffic movement across city streets and intersections**.  
With increasing traffic density, intersections must be regulated for safety — therefore each intersection is equipped with a **traffic light**.

The main objective of this project is to design a **thread-safe communication protocol between vehicles and intersections**, ensuring that traffic lights correctly control vehicle flow.  
You will apply concurrency concepts such as **mutexes, locks, and message queues** to implement this behavior.

---

## 🧠 Core Concepts

- Multi-threaded simulation of vehicles
- Traffic lights controlling intersections
- Thread-safe communication between system components
- Use of concurrency primitives:
  - **Mutexes**
  - **Locks**
  - **Message queues**

---

## 📦 Dependencies

Make sure the following tools and libraries are installed:

- **cmake ≥ 2.8**
  - Installation guide: https://cmake.org/install/

- **make ≥ 4.1 (Linux/Mac) OR 3.81 (Windows)**
  - Linux: preinstalled on most systems
  - Mac: install via Xcode Command Line Tools  
    https://developer.apple.com/xcode/features/
  - Windows: http://gnuwin32.sourceforge.net/packages/make.htm

- **OpenCV ≥ 4.1**
  - Source code (version 4.1.0):  
    https://github.com/opencv/opencv/tree/4.1.0

- **gcc / g++ ≥ 5.4**
  - Linux: usually installed by default
  - Mac: installed with Xcode Command Line Tools  
    https://developer.apple.com/xcode/features/
  - Windows: recommended compiler — MinGW  
    http://www.mingw.org/

---

## 🏗️ Build Instructions

From the project root directory:

```bash
# Clone repository
git clone <repository-url>

# Create and enter build directory
mkdir build && cd build

# Build project
cmake .. && make

# Run simulation
./traffic_simulation
