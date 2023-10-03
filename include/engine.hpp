#pragma once
class Engine {
 public:
  static void Init();
  static void Terminate();

  ~Engine() = default;

 private:
  Engine() = default;
};
