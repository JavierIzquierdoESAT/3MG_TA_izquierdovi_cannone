#include "time.hpp"
#include "GLFW/glfw3.h"

void Time::Update() {
  s_delta_time_ = (float)glfwGetTime() - s_last_time_;
  s_last_time_ = (float)glfwGetTime();
}

float Time::DeltaTime() { return s_delta_time_; }
