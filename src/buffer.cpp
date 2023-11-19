#include "buffer.hpp"

#include <vector>

#include "GL/glew.h"
#include "math/vector_2.h"
#include "math/vector_3.h"

using namespace coma;

Buffer::Buffer(const void* data, unsigned int size)
    : size_{size}, valid_{true} {
  glGenBuffers(1, &buffer_id_);
  bindBuffer(Target::kTarget_Vertex_Data);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
  glGenVertexArrays(1, &vertex_array_id_);
}

Buffer::Buffer(std::vector<Vec3> pos, std::vector<Vec3> normal,
               std::vector<Vec3> color, std::vector<Vec2> uv)
    : size_{0}, valid_{true} {
  size_ = (unsigned)(pos.size() * sizeof(Vec3));
  size_ += (unsigned)(normal.size() * sizeof(Vec3));
  size_ += (unsigned)(color.size() * sizeof(Vec3));
  size_ += (unsigned)(uv.size() * sizeof(Vec2));

  glGenVertexArrays(1, &vertex_array_id_);
  bindVertexArray();

  glGenBuffers(1, &buffer_id_);
  bindBuffer(Target::kTarget_Vertex_Data);

  glBufferData(GL_ARRAY_BUFFER, size_, NULL, GL_STATIC_DRAW);

  int size = (unsigned)(pos.size() * sizeof(Vec3));
  uploadData(static_cast<void*>(pos.data()), size, 0);
  enableVertexArray(0, 3, 0, 0);

  int offset = size;
  size = (unsigned)(normal.size() * sizeof(Vec3));
  uploadData(static_cast<void*>(normal.data()), size, offset);
  enableVertexArray(1, 3, 0, offset);

  offset += size;
  size = (unsigned)(color.size() * sizeof(Vec3));
  uploadData(static_cast<void*>(color.data()), size, offset);
  enableVertexArray(2, 3, 0, offset);

  offset += size;
  size = (unsigned)(uv.size() * sizeof(Vec2));
  uploadData(static_cast<void*>(uv.data()), size, offset);
  enableVertexArray(3, 2, 0, offset);
}

Buffer::~Buffer() {
  if (valid_) {
    glDeleteBuffers(1, &buffer_id_);
    glDeleteVertexArrays(1, &vertex_array_id_);
  }
}

Buffer::Buffer(Buffer&& other) noexcept
    : buffer_id_{other.buffer_id_},
      vertex_array_id_{other.vertex_array_id_},
      size_{other.size_},
      valid_{true} {
  other.valid_ = false;
}
Buffer::Buffer(Buffer& other) noexcept
    : buffer_id_{other.buffer_id_},
      vertex_array_id_{other.vertex_array_id_},
      size_{other.size_}, 
      valid_ {true} {
  other.valid_ = false;
}
Buffer& Buffer::operator=(Buffer&& other) noexcept{
  std::swap(buffer_id_, other.buffer_id_);
  std::swap(vertex_array_id_, other.vertex_array_id_);
  return *this;
}

void Buffer::bindBuffer(const Target t) {
  switch (t) { 
    case Target::kTarget_Vertex_Data: {
      glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
      break;
    }

    case Target::kTarget_Elements: {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
      break;
    }
    default:
      printf("Bind buffer target not valid");
      break;
  }
}

void Buffer::bindVertexArray() { glBindVertexArray(vertex_array_id_); }

unsigned int Buffer::size() const { return size_; }

void Buffer::uploadData(const void* data, unsigned int size,
                        unsigned int offset) {
  bindBuffer(Target::kTarget_Vertex_Data);
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void Buffer::enableVertexArray(const unsigned int index,
                               const unsigned int size,
                               const unsigned int stride,
                               const unsigned int offset) {
  // TODO: void* cast warning fix
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
}

unsigned int Buffer::buffer_id() const { return buffer_id_; }
