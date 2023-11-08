#include "ecs/component_manager.hpp"
#include "shader_manager.hpp"

ComponentManager::ComponentManager() : current_entity_{1} {
  add_component_class<Position>();
  add_component_class<Render>();
  add_component_class<AI>();
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
unsigned ComponentManager::addTriangle(float size, ShaderManager* sp, Vec3 color) {
  unsigned res = addEntity();
  Position pos;
  pos.pos = {0, 0, 0};
  setComponent<Position>(res, pos);
  Render ren({{-size, -size, 0.0f}, {0.0f, size, 0.0f}, {size, -size, 0.0f}},
             {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
             {color, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
             {{0, 0}, {0, 0}, {0, 0}}, sp);
  setComponent<Render>(res,ren);
  return res;
}

void ComponentManager::deleteEntity(unsigned& e) {
  for (auto& it : components_) {
    it.second->removeComponent(e);
  }

  freed_entities_.push_back(e);
  e = 0;
}