#include "window.hpp"

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <optional>

#include "math/vector_3.h"
#include "math/vector_2.h"
#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "buffer.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "load_obj.hpp"
#include "jobsystem.hpp"

//data for a 3D printable figure
std::vector<coma::Vec3> pos{
  /*P1*/ {-1.0f * 10, -1.0f * 10, 0.7f * 10},
         /*P2*/ {0.0f * 10, 1.0f * 10, 0.0f * 10},
         /*P3*/ {0.0f * 10, -1.0f * 10, -1.0f * 10},
         /*P4*/ {1.0f * 10, -1.0f * 10, 0.7f * 10},


};

std::vector<coma::Vec3> nor{
  /*P1*/ {-1.0f, 1.0f, 1.0f},
         /*P2*/ {1.0f, 1.0f, 1.0f},
         /*P3*/ {1.0f, -1.0f, 1.0f},
         /*P4*/ {-1.0f, -1.0f, 1.0f},


};

std::vector<coma::Vec2> uv{
  /*P1*/ {0.0f, 1.0f},
         /*P2*/ {1.0f, 1.0f},
         /*P3*/ {1.0f, 0.0f},
         /*P4*/ {0.0f, 0.0f},

};

std::vector<coma::Vec3> col{
  /*P1*/ {1.0f, 0.0f, 0.0f},
         /*P2*/ {1.0f, 0.0f, 0.0f},
         /*P3*/ {1.0f, 0.0f, 0.0f},
         /*P4*/ {1.0f, 0.0f, 0.0f},


};

short int order[] = {
  //Front
  0, 1, 2,
  2, 1, 3,
  3, 1, 0,
  2, 3, 0

};



int main(int, char**) {
  Engine e;
  ComponentManager component_manager;
  std::vector<std::future<std::optional<Mesh>>> resultado;

  auto w = Window::Make(e, 640, 480, "ventana");
  auto shade = ShaderManager::MakeShaders("../assets/obj.fs",
                                          "../assets/obj.vs").value();
  std::vector<Render> r;
  
  e.loadObj("../assets/obj/javi.obj");
  e.loadObj("../assets/obj/stool.obj");
  std::vector<Mesh> m = e.waitMeshLoad();

  //add the meshes of the OBJ to the ecs
  Position p(0.0f, 0.0f, 0.0f);
  AI ai;
  for (int x = 0; x < m.size(); x++) {
    r = m[x].createBuffers(shade);
    for (int i = 0; i < r.size(); i++) {
      component_manager.addEntity<Position, AI, Render>(p, ai, r[i]);
    }
  }
  float t = 0;


  while (!w.isDone()) {


    shade.setUniformValue(DataType::FLOAT_1, &t, "time");

    //render the obj
    RenderSystem(component_manager.getSparseList<Position>(),
                 component_manager.getSparseList<Render>());
    t += Time::DeltaTime();
    w.update();
  }

  
  return 0;
}
