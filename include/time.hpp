#pragma once
#include "engine.hpp"
class Time {
 public:
  Time() = delete;
  ~Time() = delete;
  static float delta_time();
  friend Engine;

 private:
  static void Update();
  inline static float s_delta_time_;
  inline static float s_last_time_;
};  // namespace Time
