#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "jobsystem.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void basic(int a, int b) {

    printf("%d, %d \n", a, b);

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
    // TODO: prety hard user usage
    //auto mycall = [ente]() { return Texture::LoadTexture(ente.c_str()); };

    //std::function<std::optional<Texture>()> f = mycall;

     resultado.push_back(std::move(b.addTask2(Texture::LoadTexture,ente.c_str())));
  }


  
  b.addTask2(basic,100,200);


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
