#pragma once

class Engine {
 public:

  Engine();
  ~Engine();

  void initShaders();

 private:
  
  
  unsigned int default_shader_program_;
  
};
