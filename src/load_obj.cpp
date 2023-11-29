#include "tiny_obj_loader.h"
#include "math/vector_2.h"
#include "math/vector_3.h"
#include <iostream>
#include "buffer.hpp"
#include "load_obj.hpp"

std::vector<Buffer> loadObj(std::string dir) {

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::vector<Buffer> bb;
    std::vector<coma::Vec3> pos;
    std::vector<coma::Vec3> nor;
    std::vector<coma::Vec3> col;
    std::vector<coma::Vec2> uv;

    coma::Vec3 posi;
    coma::Vec3 norma;
    coma::Vec3 color;
    coma::Vec2 uvs;

    std::string err;
    std::string war;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &war, &err, dir.c_str());

    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        pos.clear();
        nor.clear();
        uv.clear();
        col.clear();


            for (size_t v = 0; v < attrib.vertices.size()/3; v++) {

                posi.x = attrib.vertices[(size_t)3 * (size_t)v + (size_t)0];
                posi.y = attrib.vertices[(size_t)3 * (size_t)v + (size_t)1];
                posi.z = attrib.vertices[(size_t)3 * (size_t)v + (size_t)2];
                pos.emplace_back(posi);

                if (!attrib.normals.empty()) {
                    norma.x = attrib.normals[(size_t)3 * (size_t)v + (size_t)0];
                    norma.y = attrib.normals[(size_t)3 * (size_t)v + (size_t)1];
                    norma.z = attrib.normals[(size_t)3 * (size_t)v + (size_t)2];
                }
                else {
                    norma.x = 0;
                    norma.y = 0;
                    norma.z = 0;
                }
     
                nor.emplace_back(norma);

                if (!attrib.colors.empty()) {
                    color.x = attrib.colors[(size_t)3 * (size_t)v + (size_t)0];
                    color.y = attrib.colors[(size_t)3 * (size_t)v + (size_t)1];
                    color.z = attrib.colors[(size_t)3 * (size_t)v + (size_t)2];
                }
                else {
                    color.x = 0;
                    color.y = 0;
                    color.z = 0;
                }
                col.emplace_back(color);

                if (!attrib.texcoords.empty()) {
                    uvs.x = attrib.texcoords[(size_t)2 * (size_t)v + (size_t)0];
                    uvs.y = attrib.texcoords[(size_t)2 * (size_t)v + (size_t)1];
                }
                else {
                    uvs.x = 0;
                    uvs.y = 0;
                }
      
                uv.emplace_back(uvs);
                

            }

        Buffer b = Buffer(pos,nor,col,uv);
        bb.emplace_back(b);
       
    }

    

    return bb;

}

std::vector<Buffer> loadObjIndex(std::string dir) {

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::vector<Buffer> bb;
    std::vector< short int> indx;


    std::string err;
    std::string war;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &war, &err, dir.c_str());

    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
  
        indx.clear();
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                 short int i = (short int)idx.vertex_index;
                indx.emplace_back(i);
                //indx.push_back(idx.normal_index);
                //indx.push_back(idx.texcoord_index);




            }
            index_offset += fv;


        }
        Buffer b = Buffer(static_cast<void*>(indx.data()), indx.size() * sizeof(short int));
        bb.emplace_back(b);
    }

    
    
    return bb;

}