#pragma once

class Window;

struct Vec3 {
  float x, y, z;
};

struct Vertex {
  Vec3 position_;
  // Vec3 colors_;
  // Vec3 normal_;
};

class Triangle {
 public:
  
  ~Triangle();

  static std::optional<Triangle> Init();

  unsigned int vao() const { return vao_; };

 private:
  Triangle();

  unsigned int vao_;
  unsigned int vbo_;

  const int num_vertex_ = 3;
  Vertex vertex_[3];
};

void paint(Triangle& t, Window& w);