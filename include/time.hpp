#pragma once
#include "engine.hpp"

/// @brief static functions to retrieve time-relatated information
class Time {
 public:
  Time() = delete;
  ~Time() = delete;

  /// @brief retrieves duration of the last frame
  /// @return duration of the last frame aka: delta_time
  static float delta_time();

 private:
  friend Engine;
  static void Update();
  inline static float s_delta_time_;
  inline static float s_last_time_;
};  // namespace Time
