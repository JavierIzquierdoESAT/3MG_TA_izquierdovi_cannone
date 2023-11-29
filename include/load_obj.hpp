#pragma once
#include <iostream>
#include "math/vector_2.h"
#include "math/vector_3.h"
#include <vector>
#include <optional>
#include "tiny_obj_loader.h"


class Mesh {
public:
    
    ~Mesh() = default;

    static std::optional<Mesh> loadObj(std::string dir);
    std::vector<struct Render> createBuffers(class ShaderManager& sh);

    tinyobj::attrib_t attrib_;
    std::vector<tinyobj::shape_t> shapes_;
    std::vector<tinyobj::material_t> materials_;

private:
    Mesh();

};
