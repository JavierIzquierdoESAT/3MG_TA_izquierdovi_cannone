#include "tiny_obj_loader.h"
#include "math/vector_2.h"
#include "math/vector_3.h"
#include <iostream>
#include "buffer.hpp"
#include "load_obj.hpp"

Buffer* loadObj(std::string dir) {

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::vector<Vec3> pos;
    std::vector<Vec3> nor;
    std::vector<Vec3> col;
    std::vector<Vec2> uv;

    Vec3 posi;
    Vec3 norma;
    Vec3 color;
    Vec2 uvs;

    std::string err;
    std::string war;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &war, &err, dir.c_str());

    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    if (!ret) {
        return nullptr;
    }

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                posi.x = attrib.vertices[(size_t)3 * (size_t)idx.vertex_index + (size_t)0];
                posi.y = attrib.vertices[(size_t)3 * (size_t)idx.vertex_index + (size_t)1];
                posi.z = attrib.vertices[(size_t)3 * (size_t)idx.vertex_index + (size_t)2];
                pos.emplace_back(posi);

                norma.x = attrib.normals[(size_t)3 * (size_t)idx.normal_index + (size_t)0];
                norma.y = attrib.normals[(size_t)3 * (size_t)idx.normal_index + (size_t)1];
                norma.z = attrib.normals[(size_t)3 * (size_t)idx.normal_index + (size_t)2];
                nor.emplace_back(norma);

                color.x = attrib.colors[(size_t)3 * (size_t)idx.vertex_index + (size_t)0];
                color.y = attrib.colors[(size_t)3 * (size_t)idx.vertex_index + (size_t)1];
                color.z = attrib.colors[(size_t)3 * (size_t)idx.vertex_index + (size_t)2];
                col.emplace_back(color);

                uvs.x = attrib.texcoords[(size_t)2 * (size_t)idx.texcoord_index + (size_t)0];
                uvs.y = attrib.texcoords[(size_t)2 * (size_t)idx.texcoord_index + (size_t)1];
                uv.emplace_back(uvs);
                

            }
            index_offset += fv;


        }
    }

    Buffer b = Buffer(pos,nor,col,uv);

    return &b;

}