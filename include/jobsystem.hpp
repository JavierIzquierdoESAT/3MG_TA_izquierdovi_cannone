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

  void work();
  void set_stop(bool t);
  void add(std::function<void()> task);

 private:
  bool stop_;
  std::condition_variable condition_;
  std::mutex mutex_;
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> jobs_;
};