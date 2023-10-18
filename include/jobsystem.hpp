#pragma once
#include <chrono>
#include <future>
#include <iostream>
#include <optional>
#include <queue>
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

  /// @brief adds functions to the execution list and tells a thread to pick it
  /// up
  /// @param task the function you want to add to the list

  //template <class Return, class... Args>
  //std::future<Return> addTask(std::function<Return(Args... ar)>func);

  template <class Return, class... Args>
  std::future<Return> addTask(std::function<Return(Args... ar)> func) {
    std::shared_ptr<std::packaged_task<Return()>> task =
        std::make_shared<std::packaged_task<Return()>>(std::move(func));

    std::future<Return> future = task->get_future();
    add([task]() { (*task)(); });
    return std::move(future);
  }

 private:
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
