#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "time.hpp"

Engine::Engine() { glfwInit(); }

Engine::~Engine() { glfwTerminate(); }

void Engine::update() { Time::Update(); }
