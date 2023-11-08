#pragma once

#include <vector>

class Vec2;
class Vec3;

class Buffer {
 public:
  enum class Target {
    kTarget_Vertex_Data,
    kTarget_Elements,
  };

  Buffer() = delete;
  Buffer(Buffer&& other) noexcept;
  Buffer& operator=(Buffer&& other) noexcept;
  Buffer(Buffer& other) noexcept;
  Buffer(const Buffer& other) = delete;
  Buffer(std::vector<Vec3> pos, std::vector<Vec3> normal,
         std::vector<Vec3> color, std::vector<Vec2> uv);
  Buffer(const void* data, unsigned int size);

  ~Buffer();

  /// @brief   binds a buffer object to the specified buffer binding point
  /// @param t arget to which the buffer object is bound
  /// must be  kTarget_Vertex_Data o kTarget_Elements
  void bindBuffer(const Target t);
  void bindVertexArray();

  /// @brief Get the size of the buffer
  /// @return return the size of the buffer
  unsigned int size() const;

  /// @brief Add or update the data of the buffer
  /// @param data the information you won to set in the buffer
  /// @param size indicates the space occupied by what you want to add to the
  /// buffer
  /// @param offset Specifies the offset into the buffer object's data store
  /// where data replacement will begin, measured in bytes.
  void uploadData(const void* data, unsigned int size, unsigned int offset = 0);

  /// @brief set and activate a vertex array attribute
  /// @param size specifies the number of atribute components of te vertex can
  /// be from 1 to 4
  /// @param stride specyfie the bytes offset between consecutive datas
  /// @param offset specifie the position og the generic vertex attribute in the
  /// array
  void enableVertexArray(const unsigned int index, const unsigned int size,
                         const unsigned int stride, const unsigned int offset);
  /// @brief Get the buffer id
  /// @return the buffer id
  unsigned int buffer_id() const;

 private:
  unsigned int buffer_id_;
  unsigned int vertex_array_id_;
  unsigned int size_;
  bool valid_;
};
