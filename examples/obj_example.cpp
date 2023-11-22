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
    /*P1*/     {-1.0f * 10,  -1.0f * 10, 0.7f * 10},
    /*P2*/      {0.0f * 10,  1.0f * 10, 0.0f * 10},
    /*P3*/      {0.0f * 10, -1.0f * 10, -1.0f * 10}, 
    /*P4*/     {1.0f * 10, -1.0f * 10, 0.7f * 10}, 


};

std::vector<Vec3> nor{
    //  position  //        //    normals   //       // UV   //      //       Color      //
    /*P1*/     {-1.0f,  1.0f, 1.0f},
    /*P2*/      {1.0f,  1.0f, 1.0f},
    /*P3*/      {1.0f, -1.0f, 1.0f}, 
    /*P4*/     {-1.0f, -1.0f, 1.0f},


};

std::vector<Vec2> uv{
    //  position  //        //    normals   //       // UV   //      //       Color      //
    /*P1*/     { 0.0f, 1.0f},
    /*P2*/      { 1.0f, 1.0f},
    /*P3*/      {1.0f,  0.0f},
    /*P4*/     {0.0f,  0.0f},

};

std::vector<Vec3> col{
    //  position  //        //    normals   //       // UV   //      //       Color      //
    /*P1*/     {1.0f, 0.0f, 0.0f},
    /*P2*/      {1.0f, 0.0f, 0.0f},
    /*P3*/      {1.0f, 0.0f, 0.0f}, 
    /*P4*/     {1.0f, 0.0f, 0.0f},


};

short int order[] = {
    //Front
    0,1,2,
    2,1,3,
    3,1,0,
    2,3,0

};



int main(int, char**) {
    Engine e;

    //glCullFace(GL_FRONT_AND_BACK);
    //glEnable(GL_DEPTH_TEST);
    

    auto w = Window::Make(e, 640, 480, "ventana");
    auto obj = Buffer(pos, nor, col, uv); // loadObj("../assets/javi.obj");
    auto idxobj = Buffer(order, sizeof(order)); // loadObjIndex("../assets/javi.obj");
    auto shade = ShaderManager::MakeShaders("../assets/obj.fs", "../assets/obj.vs").value();
    float t = 0;
    if (w) {
        auto& window = w.value();

        while (!window.isDone()) {
           

            shade.setUniformValue(DataType::FLOAT_1, &t, "time");

            for (int i = 0; i < obj.size(); i++) {
                
                obj.bindBuffer(Buffer::Target::kTarget_Vertex_Data);
                obj.bindVertexArray();
                idxobj.bindBuffer(Buffer::Target::kTarget_Elements);

                shade.useProgram();
                //glDrawArrays(GL_TRIANGLES, 0, obj[i].size());
                glDrawElements(GL_TRIANGLES, 3*4, GL_UNSIGNED_SHORT, 0);
                glBindVertexArray(0);
            }
            t+=Time::delta_time();
            window.swap();
            e.update();
        }
    }

    return 0;
}
