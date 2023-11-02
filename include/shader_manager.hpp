#pragma once
enum ShaderType {
  kFragmentShader = 0,
  kVertexShader,
};

class ShaderManager {
 public:
 
  ~ShaderManager();

  //TODO: Create a Make for this class and follow RAII 
  static ShaderManager* MakeShaders(const std::string& file_fragment, const std::string& file_vertex);

  /// @brief attaches a shader object to a program object
  void attachShaders();

  /// @brief installs a program object as part of current rendering state
  void useProgram();

  // TODO: This function isn't implemented
  void setUniformValue(const int uniform_pos, const float* number);

 private:
     ShaderManager();

  unsigned int default_shader_program_;
  unsigned int vertex_shader_id_;
  unsigned int fragment_shader_id_;
};
