#include <cassert>
#include <iostream>
#include <memory>
#include <optional>
#include <tuple>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "ecs.hpp"


int main(int, char**) {
  ComponentManager component_manager;

  unsigned player = component_manager.addTriangle();

  while (true) {


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