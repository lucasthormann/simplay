#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <functional>
#include <random>

// Define the Simulation Object Class
class SimulationObject {
  public: 
    virtual void update(double delta_time) = 0;
    virtual void render() = 0;
    virtual ~SimulationObject() = default;
};

// Implement a Particle class as an example of a Simulation Object
class Particle : public SimulationObject {
  double position;
  double velocity;

public:
  Particle(double pos, double vel) : position(pos), velocity(vel) {}

  void update(double delta_time) override {
    position += velocity * delta_time;

  }

  void render() override {
    std::cout << "Particle at position: " << position << std::endl;
  }

};

// Define the Simulator class
class Simulator {
  std::vector<std::unique_ptr<SimulatorObject>> objects;
  bool running;
  std::chrono::steady_clock::time_point last_time;

public:
  Simulator() : running(false) {}


