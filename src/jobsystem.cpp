#include "jobsystem.hpp"

JobSystem::JobSystem() : stop_{false} {
  auto worker_count = std::thread::hardware_concurrency();
  for (int i = 0; i != worker_count; i++) {
    workers_.emplace_back(std::thread(&JobSystem::work, this));
  }
  std::cout << worker_count << std::endl;
}

void JobSystem::work() {
  while (true) {
    std::function<void()> task;
    {
      // el unique locl se deve usar en wait
      std::unique_lock<std::mutex> lock(mutex_);
      // mantiene al hilo esperando hasta que se cumpla alguna de las
      // condiciones
      condition_.wait(lock, [this] { return !jobs_.empty() || stop_; });

      if (stop_ && jobs_.empty()) return;
      task = std::move(jobs_.front());
      jobs_.pop();

    }  // Es importante soltar el lock antes de empezar la tarea.
    task();
  }
}

void JobSystem::set_stop(bool t) {
  stop_ = t;
  condition_.notify_all();
}

void JobSystem::add(std::function<void()> task) {
  std::lock_guard<std::mutex> lock(mutex_);
  jobs_.push(std::move(task));
  // notifica a uno de los wait que algun valor ha cambiado
  condition_.notify_one();
}

JobSystem::~JobSystem() {
  condition_.notify_all();
  for (auto& t : workers_) {
    if (t.joinable()) {
      t.join();
    }
  }
}
