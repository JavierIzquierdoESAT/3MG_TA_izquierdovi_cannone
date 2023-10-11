#include <functional>
#include <future>
#include <iostream>
#include <queue>

std::string getString(std::string a) {
   return a;
}

class Texture {};

Texture load_texture(std::string texture);

class JobSystem {
 public:
  // template<typename Function>
  // auto add_complicaete(Function task()) -> std::future<decltype(Function())>
  // { 	using Ret = decltype(Function()); 	auto t =
  //std::packaged_task<Ret()>(task); 	std::future<Ret> future = t.get_future();
  //	jobs_.push(t);

  //	return future;
  //}

  JobSystem() : stop_{false}{
    auto worker_count = std::thread::hardware_concurrency();
    for (int i = 0; i != worker_count; i++) {
      workers_.emplace_back(std::thread(&JobSystem::work, this));
    }
  }

  void work() {
    while (true) {
      std::function<void()> task;
      {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !jobs_.empty() || stop_; });
        if (stop_ && jobs_.empty()) return;
        task = std::move(jobs_.front());
        jobs_.pop();

      }  // Es importante soltar el lock antes de empezar la tarea.
      task();
    }
  }
  void set_stop(bool t) {stop_ = t;}

  void add(std::function<void()> task) { jobs_.push(std::move(task)); }

 private:
  bool stop_;
  std::condition_variable condition_;
  std::mutex mutex_;
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> jobs_;
};

int main(int, char**) {
  JobSystem b;

  std::vector<std::string> comida{"patata.jpg", "melon.jpg", "zanahoria.jpg",
                                  "pimiento.jpg"};
  std::vector<std::future<std::string>> resultado;

  for (auto& ente : comida) {
    auto mycall = [ente]() { return getString(ente); };
    auto task = std::packaged_task<std::string()>(std::move(mycall));
    std::future<std::string> future = task.get_future();
    b.add(std::move(task));
    //resultado.emplace_back(future);
  }

  struct lamba {
     auto ente;
    std::string lambda::operator()(ente) {}
  };

  return 0;
}