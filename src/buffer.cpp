#include "buffer.hpp"

#include "GL/glew.h"

Buffer::Buffer(unsigned int size) : size_{size} {
  glGenBuffers(1, &buffer_id_);
  bindBuffer(kTarget_Vertex_Data);
  glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
}

Buffer::Buffer(const void* data, unsigned int size) : size_{size} {
  glGenBuffers(1, &buffer_id_);
  bindBuffer(kTarget_Vertex_Data);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Buffer::~Buffer() {
  glDeleteBuffers(1, &buffer_id_);
  glDeleteVertexArrays(1, &vertex_array_id_);
}

void Buffer::bindBuffer(const Target t) {
  switch (t) {
    case kTarget_Vertex_Data: {
      glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
      break;
    }

    case kTarget_Elements: {
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
  bindBuffer(kTarget_Vertex_Data);
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void Buffer::updateData(const void* data, unsigned int size) {
  
  bindBuffer(kTarget_Vertex_Data);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 12, size, data);
  
}

void Buffer::reset(const void* data, unsigned int size) {
  glDeleteBuffers(1, &buffer_id_);
  glDeleteVertexArrays(1, &vertex_array_id_);

  //glGenBuffers(1, &buffer_id_);
  //bindBuffer(kTarget_Vertex_Data);
  //glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Buffer::enableVertexArray(const unsigned int size,
                               const unsigned int stride,
                               const unsigned int offset) {
  // TODO:: UNHARCODE this part. Now is set to print a triangle vertex with
  // color
  glGenVertexArrays(1, &vertex_array_id_);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
  glEnableVertexAttribArray(1);

  bindVertexArray();
}

unsigned Buffer::buffer_id() const { return buffer_id_; }
