#include "ecs.hpp"
#include "math/vector_3.h"

int main(int, char**) {
  ComponentManager component_manager;

  unsigned player = component_manager.addTriangle();

  while (true) {
    render_system(component_manager.getAll<Position>(),
                  component_manager.getAll<Render>());

    // if (input.acceleration) {
    //  // Previous code
    //  // auto [_, ph, ___] = component_manager.get_entity(player);
    //  ph->acceleration += 1;
    //}
    // Previous code
    //		physics_system(component_manager.position,
    // component_manager.physics);
  }
  return 0;
}