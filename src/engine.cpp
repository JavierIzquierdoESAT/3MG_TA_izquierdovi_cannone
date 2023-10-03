#include "engine.hpp"

#include <GLFW/glfw3.h>

Engine::Engine() { glfwInit(); }

Engine::~Engine() { glfwTerminate(); }
