#include "window.hpp"

#include <array>
#include <iostream>
#include <string>

#include "math/vector_3.h"
#include "math/vector_2.h"
#include "engine.hpp"
#include "buffer.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "load_obj.hpp"


std::vector<Vec3> pos{
    //  position  //        //    normals   //       // UV   //      //       Color      //
    /*P1*/     {-1.0f * 10,  1.0f * 10, 1.0f * 10},
    /*P2*/      {1.0f * 10,  1.0f * 10, 1.0f * 10},
    /*P3*/      {1.0f * 10, -1.0f * 10, 1.0f * 10}, 
    /*P4*/     {-1.0f * 10, -1.0f * 10, 1.0f * 10}, 

    /*P1*/     {-1.0f * 10,  1.0f * 10, -1.0f * 10}, 
    /*P2*/      {1.0f * 10,  1.0f * 10, -1.0f * 10}, 
    /*P3*/      {1.0f * 10, -1.0f * 10, -1.0f * 10}, 
    /*P4*/     {-1.0f * 10, -1.0f * 10, -1.0f * 10}, 
};

std::vector<Vec3> nor{
    //  position  //        //    normals   //       // UV   //      //       Color      //
    /*P1*/     {-1.0f,  1.0f, 1.0f},
    /*P2*/      {1.0f,  1.0f, 1.0f},
    /*P3*/      {1.0f, -1.0f, 1.0f}, 
    /*P4*/     {-1.0f, -1.0f, 1.0f},
    /*P1*/     {-1.0f,  1.0f, -1.0f},
    /*P2*/      {1.0f,  1.0f, -1.0f},
    /*P3*/      {1.0f, -1.0f, -1.0f},
    /*P4*/     {-1.0f, -1.0f, -1.0f}, 

};

std::vector<Vec2> uv{
    //  position  //        //    normals   //       // UV   //      //       Color      //
    /*P1*/     { 0.0f, 1.0f},
    /*P2*/      { 1.0f, 1.0f},
    /*P3*/      {1.0f,  0.0f},
    /*P4*/     {0.0f,  0.0f},

    /*P1*/     {0.0f,  1.0f},
    /*P2*/      {1.0f,  1.0f},
    /*P3*/      {1.0f,  0.0f},
    /*P4*/     { 0.0f,  0.0f},
};

std::vector<Vec3> col{
    //  position  //        //    normals   //       // UV   //      //       Color      //
    /*P1*/     {1.0f, 0.0f, 0.0f},
    /*P2*/      {1.0f, 0.0f, 0.0f},
    /*P3*/      {1.0f, 0.0f, 0.0f}, 
    /*P4*/     {1.0f, 0.0f, 0.0f},

    /*P1*/     {1.0f,  0.0f, 0.0f}, 
    /*P2*/      {1.0f, 0.0f, 0.0f}, 
    /*P3*/      {1.0f, 0.0f, 0.0f}, 
    /*P4*/     {1.0f, 0.0f,  0.0f},

};

short int order[] = {
    //Front
    2,0,3,
    2,1,0,

    //Right
    1,2,6,
    6,5,1,

    //Back
    7,4,5,
    5,6,7,

    //Left
    4,7,3,
    3,0,4,

    //Top
    4,0,1,
    1,5,4,

    //Bot
    3,7,6,
    6,2,3

};


int main(int, char**) {
    Engine e;

    glCullFace(GL_FRONT_AND_BACK);
    glEnable(GL_DEPTH_TEST);
    

    auto w = Window::Make(e, 640, 480, "ventana");
    auto obj = /*Buffer(pos, nor, col, uv); */ loadObj("../assets/javi.obj");
    auto idxobj = /*Buffer(order, sizeof(order)); */ loadObjIndex("../assets/javi.obj");
    auto shade = ShaderManager::MakeShaders("../assets/obj.fs", "../assets/obj.vs").value();

    if (w) {
        auto& window = w.value();

        while (!window.isDone()) {
            float t = Time::delta_time();

            shade.setUniformValue(DataType::FLOAT_1, &t, "time");

            for (int i = 0; i < obj.size(); i++) {
                
                //obj[i].bindBuffer(Buffer::Target::kTarget_Vertex_Data);
                obj[i].bindVertexArray();
                idxobj[i].bindBuffer(Buffer::Target::kTarget_Elements);

                shade.useProgram();
                //(GL_TRIANGLES, 0, obj.size() / 11);
                glDrawElements(GL_TRIANGLES, idxobj[i].size(), GL_UNSIGNED_INT, nullptr);
                glBindVertexArray(0);
            }

            window.swap();
            e.update();
        }
    }

    return 0;
}
