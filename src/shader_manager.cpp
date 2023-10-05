#include "shader_manager.hpp"

#include <fstream>

// TODO: Move this out of here
const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aCol;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "   color = aCol;\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 color;"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(color.x, color.y, color.z, 1.0f);\n"
    "}\n\0";

ShaderManager::ShaderManager() { default_shader_program_ = glCreateProgram(); }

ShaderManager::~ShaderManager() { glDeleteProgram(default_shader_program_); }

void ShaderManager::generateAndCompileShader(ShaderType t,
                                             const std::string& fil) {
  switch (t) {
    case kFragmentShader:
      fragment_shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment_shader_id_, 1, &fragmentShaderSource, NULL);
      glCompileShader(fragment_shader_id_);

      GLint vertex_compiled;
      glGetShaderiv(fragment_shader_id_, GL_COMPILE_STATUS, &vertex_compiled);
      if (vertex_compiled != GL_TRUE) {
        GLsizei log_length = 0;
        char message[1024];
        glGetShaderInfoLog(fragment_shader_id_, 1024, &log_length, &message[0]);
        printf("Frag fail");
      }
      break;

    case kVertexShader:
      vertex_shader_id_ = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex_shader_id_, 1, &vertexShaderSource, NULL);
      glCompileShader(vertex_shader_id_);

      GLint v_comp;
      glGetShaderiv(vertex_shader_id_, GL_COMPILE_STATUS, &v_comp);
      if (v_comp != GL_TRUE) {
        GLsizei log_length = 0;
        char message[1024];
        glGetShaderInfoLog(vertex_shader_id_, 1024, &log_length, &message[0]);
        printf("Vertex fail");
        printf("%s", message);
      }
      break;
    default:
      printf("Shader not valid\n");
      break;
  }
}

void ShaderManager::atachShaders() {
  glAttachShader(default_shader_program_, vertex_shader_id_);
  glAttachShader(default_shader_program_, fragment_shader_id_);
  glLinkProgram(default_shader_program_);

  glUseProgram(default_shader_program_);
}

void ShaderManager::useProgram() { glUseProgram(default_shader_program_); }

void ShaderManager::setUniformValue(const int uniform_pos,
                                    const float* number) {
  // TODO:: This part will be able to set uniform variable in the shaders
  useProgram();
}

std::string ReadFiles(const std::string& file) {
  std::string final;
  std::ifstream fileStream(file, std::ios::in);

  if (!fileStream.is_open()) {
    printf("ERROR CAN'T READ FILE %s",
           file.c_str());  // <string>.c_str() = convertir el string a char
    return "No fue mi culpa";
  }

  std::string aux = "";  // poner a vacio un string
  while (!fileStream
              .eof()) {  // eof(end of file) = recorrer linea a liner el fichero
    std::getline(fileStream, aux);  // me guardo la linea del fichero
    final.append(aux + "\n");       // concateno en el resulatdo la linea
                               // anteriormente guardada con un salto de linea
  }

  fileStream.close();
  return final;
}