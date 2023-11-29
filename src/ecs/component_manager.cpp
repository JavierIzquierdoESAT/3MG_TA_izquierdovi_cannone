#include "ecs/component_manager.hpp"
#include "shader_manager.hpp"

ComponentManager::ComponentManager() : current_entity_{1} {
  addComponentClass<Position>(ComponentListType::kSparse);
  addComponentClass<Render>(ComponentListType::kSparse);
  addComponentClass<AI>(ComponentListType::kSparse);
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
    it.second->addEntity(res);
  }
  return res;
}

void ComponentManager::deleteEntity(unsigned& e) {
  for (auto& it : components_) {
    it.second->removeComponent(e);
  }

  freed_entities_.push_back(e);
  e = 0;
}