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
  
  template<typename T, typename... Args>
  void addObject(Args&&... args) {
    objects.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));

  }
  
  void start() {
   running = true;
   last_time = std::chrono::steady_clock::now();

    while (running) {
      // Calculate delta time
      auto current_time = std::chrono::steady_clock::now();
      auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - last_time);
      double delta_time = elapsed_time.count();

      //Update and render all objects
      for (auto& obj : objects) {
        obj->update(delta_time);
        obj->render();
      }

      last_time = current_time;

      // Simulate real-time delay
      std::this_thread::sleep_for(std::chrono::miliseconds(100));

      // Placeholder for a stop condition, could be replaced with user input, etc.
      if(std::chrono::steady_clock::now() - last_time > std::chrono::seconds(5)) {
        running = false;
      }
    }
  }
};

int main() {
  Simulator sim;

  // Seed with a real random value, if available
  std::random_device rd;
  std::mt19937 gen(rd());

  // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(-1.0, 1.0);

  // Initialize particles with random position and velocity
  for(int i = 0; i < 5; i++) {
    sim.addObject<Particle>(dis(gen), dis(gen));
  }

  // Start the simulation
  sim.start();

  return 0;
}
