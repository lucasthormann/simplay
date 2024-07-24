#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <functional>
#include <random>

// Define the Simulation Object Class
class SimulationObject { // Abstract base class with virtual functions allowing various objects with different behavior
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

  void update(double delta_time) override { // progresses particles position based on velocity and time elapsed
    position += velocity * delta_time;

  }

  void render() override {
    std::cout << "Particle at position: " << position << std::endl;
  }

};

// Define the Simulator class
class Simulator { // Manages simulations execution
  std::vector<std::unique_ptr<SimulationObject>> objects; // holds collection of SimulationObject pointers, allowing for diffferent types of objects in the sim
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
   last_time = std::chrono::steady_clock::now(); // steady_clock gives us a monotonic clock to measure elapsed time

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
      std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
