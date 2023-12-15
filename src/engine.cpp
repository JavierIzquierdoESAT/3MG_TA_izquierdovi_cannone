#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
}

void Engine::update() { Time::Update(); }
