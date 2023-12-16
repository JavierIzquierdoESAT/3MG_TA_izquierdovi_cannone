#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "load_obj.hpp"
#include "AL/al.h"
#include "AL/alc.h"

#include "time.hpp"

Engine::Engine() { glfwInit(); 
    device_ = alcOpenDevice(NULL);
  ctx_ = alcCreateContext(device_, NULL);
  alcMakeContextCurrent(ctx_);
}

Engine::~Engine() { 
  
  glfwTerminate(); 
  alcCloseDevice(device_);
  job_system_.set_stop(true);
}


void Engine::update() const { Time::Update(); }

void Engine::loadObj(const std::string& path) {
  loading_meshes_.
      push_back(std::move(job_system_.addTask(Mesh::loadObj, path)));
}



std::vector<Mesh> Engine::waitMeshLoad() {
  // wait for futures to be returned
  std::vector<Mesh> loaded_meshes_;
  size_t count = 0;
  bool finish = false;
  while (!finish) {
    for (auto& a : loading_meshes_) {
      if (a.valid()) {
        if (a.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
          loaded_meshes_.push_back(a.get().value());
          count++;
        }
      }
    }
    if (count == loading_meshes_.size()) finish = true;
  }
  return loaded_meshes_;
}
