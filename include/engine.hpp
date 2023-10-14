#pragma once

/// @brief generic functions that the engine requieres to run properly
class Engine {
 public:
  Engine();
  ~Engine();

  /// @brief updates internal engine stuff this function must be called once per
  /// frame
  void update();

 private:
};
