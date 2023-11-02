#pragma once
enum class DataType {
    FLOAT_1 = 0,
    FLOAT_2,
    FLOAT_3,
    FLOAT_4,
    MAT_4x4,
    MAT_3x3,
    MAT_2x2,
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
  void setUniformValue(DataType dt, const float* number, const std::string& uniform_name);

 private:
     ShaderManager();

  unsigned int default_shader_program_;
  unsigned int vertex_shader_id_;
  unsigned int fragment_shader_id_;
};
