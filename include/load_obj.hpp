#pragma once
#include <iostream>
#include "math/vector_2.h"
#include "math/vector_3.h"
#include <vector>
#include <optional>
#include "tiny_obj_loader.h"


class Mesh {
public:
    Mesh() = default;
    ~Mesh() = default;

    /// @brief Load's the data of a obj
    /// @param std::string dir: the root of the obj you want to load
    /// @return a Mesh with all the data of the obj
    static std::optional<Mesh> loadObj(std::string dir);

    /// @brief Generates the number of renderers necessary to paint all the meshes of the object
    /// @param ShaderManager& sh: the shaders to paint the mesh
    /// @return a vector with the Renderers you need to use in the ecs
    std::vector<struct Render> createBuffers(class ShaderManager& sh);

    tinyobj::attrib_t attrib_;
    std::vector<tinyobj::shape_t> shapes_;
    std::vector<tinyobj::material_t> materials_;

private:
    

};
