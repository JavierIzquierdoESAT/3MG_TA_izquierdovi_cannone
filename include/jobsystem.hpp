#pragma once
#include <chrono>
#include <future>
#include <iostream>
#include <optional>
#include <queue>
#include <thread>

/// @brief Manages multithread tasks
class JobSystem {
 public:
  JobSystem();
  ~JobSystem();

  /// @brief sets the threads and leaves them ready to receive jobs
  void work();

  /// @brief artive or unactive the status of the multy thread
  /// @param t: state to which you want to set the bool
  void set_stop(bool t);

  /// @brief adds functions to the execution list and tells a thread to pick it
  /// up
  /// @param task the function you want to add to the list and the parameteres of the function
  template <class Funct, typename... Args>
  auto addTask(Funct f, Args... a) -> std::future<decltype(f(a...))> {
    using ret = decltype(f(a...));

    std::function<ret()> fun = std::bind(f, a...);

    return setFuture(fun);
  }

 private:
  template <class Return>
  std::future<Return> setFuture(std::function<Return()> func) {
    std::shared_ptr<std::packaged_task<Return()>> task =
        std::make_shared<std::packaged_task<Return()>>(std::move(func));

    std::future<Return> future = task->get_future();
    add([task]() { (*task)(); });
    return future;
  }

  /// @brief adds functions to the execution list and tells a thread to pick
  /// it up
  /// @param task the function you want to add to the list
  void add(std::function<void()> task);

  bool stop_;
  std::condition_variable condition_;
  std::mutex mutex_;
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> jobs_;
};
