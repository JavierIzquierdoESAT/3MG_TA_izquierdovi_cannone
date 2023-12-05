#include <array>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "buffer.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "jobsystem.hpp"
#include "load_obj.hpp"
#include "math/vector_2.h"
#include "math/vector_3.h"
#include "shader_manager.hpp"
#include "time.hpp"
#include "window.hpp"

// data for a 3D printable figure
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
    // Front
    0, 1, 2, 2, 1, 3, 3,
    1, 0, 2, 3, 0

};

int main(int, char**) {
  Engine e;
  ComponentManager component_manager;
  JobSystem j;
  std::vector<std::future<std::optional<Mesh>>> resultado;

  auto w = Window::Make(e, 640, 480, "ventana");
  auto shade =
      ShaderManager::MakeShaders("../assets/obj.fs", "../assets/obj.vs")
          .value();
  std::vector<Render> r;
  std::vector<Mesh> m;

  // add 2 obj in the job system
  std::string obj1 = "../assets/obj/pollo.obj";
  std::string obj3 = "../assets/obj/stool.obj";
  std::string obj4 = "../assets/obj/sword_shield.obj";
  std::string obj5 = "../assets/obj/torch.obj";

  resultado.push_back(std::move(j.addTask(Mesh::loadObj, obj1)));
  resultado.push_back(std::move(j.addTask(Mesh::loadObj, obj3)));
  resultado.push_back(std::move(j.addTask(Mesh::loadObj, obj4)));
  resultado.push_back(std::move(j.addTask(Mesh::loadObj, obj5)));

  // wait for futures to be returned
  int count = 0;
  bool finish = false;
  while (!finish) {
    for (auto& a : resultado) {
      if (a.valid()) {
        if (a.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
          m.push_back(a.get().value());
          count++;
        }
      }
    }
    if (count == resultado.size()) finish = true;
  }

  // add the meshes of the OBJ to the ecs
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

    // render the obj
    RenderSystem(component_manager.getAll<Position>(),
                 component_manager.getAll<Render>());
    t += Time::DeltaTime();
    w.update();
  }

  return 0;
}
