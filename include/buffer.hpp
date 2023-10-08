#pragma once

class Buffer {
 public:
  enum Target {
    kTarget_Vertex_Data,
    kTarget_Elements,
  };

  Buffer() = delete;
  Buffer(unsigned int size);
  Buffer(const void* data, unsigned int size);

  ~Buffer();

  void bindBuffer(const Target t);
  void bindVertexArray();

  unsigned int size() const;

  void uploadData(const void* data, unsigned int size, unsigned int offset = 0);

  void updateData(const void* data, unsigned int size);

  void reset(const void* data, unsigned int size);

  void enableVertexArray(const unsigned int size, const unsigned int stride,
                         const unsigned int offset);

  unsigned buffer_id() const;

 private:
  unsigned int buffer_id_;
  unsigned int vertex_array_id_;
  unsigned int size_;

};
