#pragma once
#include <future>
#include <iostream>
#include <optional>
#include <queue>

#include <chrono>
#include <thread>

class JobSystem {
 public:

  JobSystem();
  ~JobSystem();

  /// @brief sets the threads and leaves them ready to receive jobs
  void work();

  /// @brief artive or unactive the status of the multy thread 
  /// @param t: state to which you want to set the bool 
  void set_stop(bool t);

  /// @brief adds functions to the execution list and tells a thread to pick up
  /// @param task the function you want to add to the list
  void add(std::function<void()> task);

 private:
  bool stop_;
  std::condition_variable condition_;
  std::mutex mutex_;
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> jobs_;
};