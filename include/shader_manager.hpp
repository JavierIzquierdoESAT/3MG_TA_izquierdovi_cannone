#pragma once
enum ShaderType {
  kFragmentShader = 0,
  kVertexShader,
};

class ShaderManager {
 public:
  ShaderManager();
  ~ShaderManager();

  void generateAndCompileShader(ShaderType t, const std::string& file_path);

  void atachShaders();

  void useProgram();

  void setUniformValue(const int uniform_pos, const float* number);

 private:
  unsigned int default_shader_program_;
  unsigned int vertex_shader_id_;
  unsigned int fragment_shader_id_;
};
