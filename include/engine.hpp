#pragma once
#include "jobsystem.hpp"
#include "load_obj.hpp"

/// @brief generic functions that the engine requieres to run properly
class Engine {
public:
  Engine();
  ~Engine();

  /// @brief updates internal engine stuff this function must be called once per
  /// frame
  void update() const;

  void loadObj(const std::string& path);

  std::vector<Mesh> waitMeshLoad();

private:
  std::vector<std::future<std::optional<Mesh>>> loading_meshes_;
  JobSystem job_system_;
};
