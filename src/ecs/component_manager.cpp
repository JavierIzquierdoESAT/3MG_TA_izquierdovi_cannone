#include "ecs/component_manager.hpp"
#include "shader_manager.hpp"

ComponentManager::ComponentManager() : current_entity_{1} {
  add_component_class<Position>(ComponentListType::kSparse);
  add_component_class<Render>(ComponentListType::kSparse);
  add_component_class<AI>(ComponentListType::kSparse);
}

unsigned ComponentManager::addEntity() {
  unsigned res;
  if (freed_entities_.size() > 0) {
    res = freed_entities_[freed_entities_.size() - 1];
    freed_entities_.pop_back();
  } else {
    res = current_entity_;
    current_entity_++;
  }

  for (auto& it : components_) {
    it.second->addComponent(res);
  }
  return res;
}

//TODO: smelly
unsigned ComponentManager::addTriangle(float size, ShaderManager& sp, coma::Vec3 color) {
  Position pos(0,0,0);
  Render ren = Render::MakeTriangle(size, color, sp);
  unsigned res = addEntity(pos, ren);
  return res;
}

void ComponentManager::deleteEntity(unsigned& e) {
  for (auto& it : components_) {
    it.second->removeComponent(e);
  }

  freed_entities_.push_back(e);
  e = 0;
}