#include "ecs/component_manager.hpp"

ComponentManager::ComponentManager() : current_entity_{1} {
  add_component_class<Position>();
  add_component_class<Render>();
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

unsigned ComponentManager::addTriangle() {
  unsigned res = addEntity();
  Position pos;
  pos.pos = {0, 0, 0};
  setComponent<Position>(res, pos);
  Render ren;
  ren.pos = {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}};
  ren.color = {
      {1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {0.0, 0.0, 1.0},
  };
  setComponent<Render>(res, ren);
  return res;
}

void ComponentManager::deleteEntity(unsigned& e) {
  for (auto& it : components_) {
    it.second->removeComponent(e);
  }

  freed_entities_.push_back(e);
  e = 0;
}