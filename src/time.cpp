#include "time.hpp"

#include "GLFW/glfw3.h"

using namespace Time;

float s_delta_time_ = 0;
float s_last_time_ = 0;

void Time::Update() {
  s_delta_time_ = (float)glfwGetTime() - s_last_time_;
  s_last_time_ = (float)glfwGetTime();
}

float Time::delta_time() { return s_delta_time_; }
