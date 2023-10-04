#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


// TODO: Move this out of here
const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


Engine::Engine() {
  glfwInit();
}

Engine::~Engine() {
  glfwTerminate();
  glDeleteProgram(default_shader_program_);
}

void Engine::initShaders() {
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  default_shader_program_ = glCreateProgram();
  glAttachShader(default_shader_program_, vertexShader);
  glAttachShader(default_shader_program_, fragmentShader);
  glLinkProgram(default_shader_program_);

  glUseProgram(default_shader_program_);
}
