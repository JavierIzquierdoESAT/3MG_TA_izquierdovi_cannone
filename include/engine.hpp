#pragma once

class Engine {
 public:

  Engine();
  ~Engine();


 private:
  void initShaders ();
  
  unsigned int default_shader_program_;
  
};
