#include "engine.hpp"

#include <GLFW/glfw3.h>

void Engine::Init() { glfwInit(); }

void Engine::Terminate() { glfwTerminate(); }
