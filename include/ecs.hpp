#include <cassert>
#include <iostream>
#include <memory>
#include <optional>
#include <tuple>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "buffer.hpp"
#include "triangle.hpp"

struct Vec3 {
  float x, y, z;
};
struct Vec2 {
  float x, y;
};

struct Position {
  Vec3 pos;
};

struct Render {
  //TODO: rendermode
  //TODO: shaderprogram
  std::vector<Vec3> pos;
  std::vector<Vec3> normal;
  std::vector<Vec3> color;
  std::vector<Vec2> uv;
};

//TODO: Tranform pos to Triangle Vertex pos

struct component_base {
  virtual void addComponent(unsigned e) = 0;
  virtual void removeComponent(unsigned e) = 0;
};

template <typename T>
struct component_list : component_base {
  void addComponent(unsigned e) override {
    if (e >= components_.size()) {
      components_.emplace_back(std::optional<T>());
    }
  }
  void removeComponent(unsigned e) override { components_[e - 1].reset(); }

  std::vector<std::optional<T>> components_;
};

class ComponentManager {
 public:
  std::unordered_map<std::size_t, std::unique_ptr<component_base>> components_;

  ComponentManager() {
    add_component_class<Position>();
    add_component_class<Position>();
  }
  template <typename T>
  void add_component_class() {
    components_.emplace(typeid(T).hash_code(),
                        std::make_unique<component_list<T>>());
  }

  unsigned addEntity() {
    unsigned res;
    if (freed.size() > 0) {
      res = freed[freed.size() - 1];
      freed.pop_back();
    } else {
      res = current_entity;
      current_entity++;
    }

    for (auto& it : components_) {
      it.second->addComponent(res);
    }
    return res;
  }
  unsigned addTriangle() {
    unsigned res = addEntity();
    Position pos;
    pos.pos = {
        {-0.5f, -0.5f, 0.0f},
        {0.0f, 0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
    };
    setComponent<Position>(res,pos);
    Render ren;
    ren.color = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
    };
    setComponent<Render>(res, ren);
    return res;
  }

  template <typename T>
  void setComponent(unsigned e, T c) {
    auto comp_base = components_.find(typeid(T).hash_code());
    component_list<T>* component_vector =
        static_cast<component_list<T>*>(comp_base->second.get());
    component_vector->components_[e - 1] = c;
  }

  void deleteEntity(unsigned& e) {
    for (auto& it : components_) {
      it.second->removeComponent(e);
    }

    freed.push_back(e);
    e = 0;
  }

  template <typename T>
  std::optional<T>& getComponent(unsigned e) {
    auto comp_base = components_.find(typeid(T).hash_code());
    component_list<T>* component_vector =
        static_cast<component_list<T>*>(comp_base->second.get());
    return component_vector->components_[e - 1];
  }

  std::vector<unsigned> freed;

 private:
  unsigned current_entity = 1;
};

void render_system(std::vector<std::optional<Position>>& positions,
                    std::vector<std::optional<Render>>& render) {

  auto p = positions.begin();
  auto ph = render.begin();

  // TODO: buffer creation
  for (; p != positions.end(); p++, ph++) {
    if (!p->has_value() || !ph->has_value()) continue;
    auto& pv = p->value();
    auto& phv = ph->value();

    // TODO: Pass render data to buffer


  
    //Render
    
  }
  assert(ph == render.end());
}