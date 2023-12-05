#include "load_obj.hpp"

#include <iostream>

#include "ecs/default_components.hpp"
#include "shader_manager.hpp"

std::optional<Mesh> Mesh::loadObj(std::string dir) {
  std::vector<Buffer> bb;
  std::optional<Mesh> mesh;
  Mesh m;
  std::string err;
  std::string war;
  tinyobj::LoadObj(&m.attrib_, &m.shapes_, &m.materials_, &war, &err,
                   dir.c_str());

  if (!err.empty()) {
    std::cerr << err << std::endl;
  } else {
    mesh.emplace(std::move(m));
  }

  return mesh;
}

std::vector<Render> Mesh::createBuffers(ShaderManager& sh) {
  std::vector<Render> rend;
  coma::Vec3 posi;
  coma::Vec3 norma;
  coma::Vec3 color;
  coma::Vec2 uvs;

  std::vector<coma::Vec3> pos;
  pos.reserve(10024);
  std::vector<coma::Vec3> nor;
  nor.reserve(10024);
  std::vector<coma::Vec3> col;
  col.reserve(10024);
  std::vector<coma::Vec2> uv;
  uv.reserve(10024);
  std::vector<short int> indx;
  indx.reserve(10024);

  for (size_t s = 0; s < shapes_.size(); s++) {
    // Loop over faces(polygon)
    pos.clear();
    nor.clear();
    uv.clear();
    col.clear();
    indx.clear();
    size_t index_offset = 0;

    for (size_t v = 0; v < attrib_.vertices.size() / 3; v++) {
      posi.x = attrib_.vertices[(size_t)3 * (size_t)v + (size_t)0];
      posi.y = attrib_.vertices[(size_t)3 * (size_t)v + (size_t)1];
      posi.z = attrib_.vertices[(size_t)3 * (size_t)v + (size_t)2];
      pos.emplace_back(posi);

      if (!attrib_.normals.empty()) {
        norma.x = attrib_.normals[(size_t)3 * (size_t)v + (size_t)0];
        norma.y = attrib_.normals[(size_t)3 * (size_t)v + (size_t)1];
        norma.z = attrib_.normals[(size_t)3 * (size_t)v + (size_t)2];
      } else {
        norma.x = 0;
        norma.y = 0;
        norma.z = 0;
      }

      nor.emplace_back(norma);

      if (!attrib_.colors.empty()) {
        color.x = attrib_.colors[(size_t)3 * (size_t)v + (size_t)0];
        color.y = attrib_.colors[(size_t)3 * (size_t)v + (size_t)1];
        color.z = attrib_.colors[(size_t)3 * (size_t)v + (size_t)2];
      } else {
        color.x = 0;
        color.y = 0;
        color.z = 0;
      }
      col.emplace_back(color);

      if (!attrib_.texcoords.empty()) {
        uvs.x = attrib_.texcoords[(size_t)2 * (size_t)v + (size_t)0];
        uvs.y = attrib_.texcoords[(size_t)2 * (size_t)v + (size_t)1];
      } else {
        uvs.x = 0;
        uvs.y = 0;
      }

      uv.emplace_back(uvs);
    }

    for (size_t f = 0; f < shapes_[s].mesh.num_face_vertices.size(); f++) {
      int fv = shapes_[s].mesh.num_face_vertices[f];

      // Loop over vertices in the face.
      for (size_t v = 0; v < fv; v++) {
        // access to vertex
        tinyobj::index_t idx = shapes_[s].mesh.indices[index_offset + v];
        short int i = (short int)idx.vertex_index;
        indx.emplace_back(i);
      }
      index_offset += fv;
    }
    rend.emplace_back(Render(pos, nor, col, uv, indx, sh));
  }

  return rend;
}
