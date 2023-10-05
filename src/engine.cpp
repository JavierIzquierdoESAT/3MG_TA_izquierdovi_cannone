#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


Engine::Engine() {
  glfwInit();
}

Engine::~Engine() {
  glfwTerminate();
}

