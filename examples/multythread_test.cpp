#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <optional>
#include <queue>
#include <thread>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string getString(std::string a) {
  std::cout << a << std::endl;
  return a;
}

class Texture {
 public:
  Texture(std::string t)
      : texture_{0} {

        };

  Texture() {
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
  }

  static std::optional<Texture> LoadTexture(const char* a) {
    // return TTest(a);
    Texture t = Texture();

    // set the texture wrapping/filtering options (on the currently bound
    // texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(a, &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
    } else {
      std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    std::cout << a << ": Loaded" << std::endl;

    return t;
  }
  unsigned int texture_;

 private:
};

class JobSystem {
 public:
  JobSystem() : stop_{false} {
    auto worker_count = std::thread::hardware_concurrency();
    for (int i = 0; i != worker_count; i++) {
      workers_.emplace_back(std::thread(&JobSystem::work, this));
    }
    std::cout << worker_count << std::endl;
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

  ~JobSystem() {
    condition_.notify_all();
    for (auto& t : workers_) {
      if (t.joinable()) {
        t.join();
      }
    }
  }

  void set_stop(bool t) { stop_ = t; }

  void add(std::function<void()> task) {
    std::lock_guard<std::mutex> lock(mutex_);
    jobs_.push(std::move(task));
    condition_.notify_one();
  }

  template <class Return, class... Args>
  std::future<Return> Tuple(std::function<Return(Args... ar)> func) {
    std::shared_ptr<std::packaged_task<Return()>> task =
        std::make_shared<std::packaged_task<Return()>>(std::move(func));

    std::future<Return> future = task->get_future();
    add([task]() { (*task)(); });
    return std::move(future);
  };

 private:
  bool stop_;
  std::condition_variable condition_;
  std::mutex mutex_;
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> jobs_;
};

int main(int, char**) {
  glfwInit();
  JobSystem b;

  std::vector<std::string> comida{"../assets/4k.png", "../assets/4k.png",
                                  "../assets/4k.png", "../assets/4k.png",
                                  "../assets/4k.png", "../assets/4k.png"};
  std::vector<std::future<std::optional<Texture>>> resultado;

  double start = glfwGetTime();
  for (auto& ente : comida) {
    //Texture t = Texture::LoadTexture(ente.c_str());
  }
  std::cout << glfwGetTime() - start << std::endl;

  start = glfwGetTime();
  for (auto& ente : comida) {
    auto mycall = [ente]() { return Texture::LoadTexture(ente.c_str()); };

    std::function<std::optional<Texture>()> f = mycall;

    resultado.push_back(std::move(b.Tuple(f)));
  }

  int count = 0;

  while (true) {
    for (auto& a : resultado) {
      if (a.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        count++;
      }
    }
    if (count == resultado.size()) break;
    count = 0;
  }

  std::cout << glfwGetTime() - start << std::endl;

  for (auto& a : resultado) {
    std::cout << a.get()->texture_;
  }

  return 0;
}