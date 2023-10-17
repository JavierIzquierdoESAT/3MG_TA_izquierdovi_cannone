#include <functional>
#include <future>
#include <iostream>
#include <optional>
#include <queue>

#include <chrono>
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

  static Texture LoadTexture(const char* a) {
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
  // template<typename Function>
  // auto add_complicaete(Function task()) -> std::future<decltype(Function())>
  // { 	using Ret = decltype(Function()); 	auto t =
  // std::packaged_task<Ret()>(task); 	std::future<Ret> future =
  // t.get_future(); 	jobs_.push(t);

  //	return future;
  //}

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
        condition_.wait(lock, [this] {
          return !jobs_.empty() || stop_;
        });

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

  std::vector<std::string> comida{
      "../assets/4k.png", "../assets/4k.png",
      "../assets/4k.png", "../assets/4k.png",
      "../assets/4k.png", "../assets/4k.png"
  };
  std::vector<std::future<std::optional<Texture>>> resultado;

  double start = glfwGetTime();
  for (auto& ente : comida) {
    Texture t = Texture::LoadTexture(ente.c_str());
  }
  std::cout << glfwGetTime() - start << std::endl;


  start = glfwGetTime();
  for (auto& ente : comida) {
    auto mycall = [ente]() { return Texture::LoadTexture(ente.c_str()); };
    std::shared_ptr<std::packaged_task<std::optional<Texture>()>> task =
        std::make_shared<std::packaged_task<std::optional<Texture>()>>(
            std::move(mycall));
    // auto task = std::packaged_task<std::string()>(std::move(mycall));
    std::future<std::optional<Texture>> future = task->get_future();
    b.add([task]() { (*task)(); });
    resultado.push_back(std::move(future));
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

// int main(int, char**) {
//  JobSystem b;
//  glfwInit();
//  std::vector<std::string> comida{"../assets/4k.png"};
//  std::vector<std::future<std::optional<std::string>>> resultado;
//
//  double start = glfwGetTime();
//  for (auto& ente : comida) {
//    // Texture t = Texture::LoadTexture(ente.c_str());
//  }
//  // std::cout << glfwGetTime() - start << std::endl;
//
//  start = glfwGetTime();
//  for (auto& ente : comida) {
//    auto mycall = [ente]() { return TTest::getString(ente); };
//
//    std::shared_ptr<std::packaged_task<std::optional<std::string>()>> task;
//    task = std::make_shared<std::packaged_task<std::optional<std::string>()>>(
//        std::move(mycall));
//
//    std::future<std::optional<std::string>> future = task->get_future();
//    b.add([task]() { (*task)(); });
//    resultado.push_back(std::move(future));
//  }
//
//  while (resultado[0].wait_for(std::chrono::seconds(0)) !=
//         std::future_status::ready) {
//  }
//  std::cout << glfwGetTime() - start << std::endl;
//
//  // int count = 0;
//
//  // while (true) {
//  //  for (auto& a : resultado) {
//  //    if (a.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
//  {
//  //      count++;
//  //    }
//  //  }
//  //  if (count == resultado.size()) break;
//  //  count = 0;
//  //}
//
//  return 0;
//}