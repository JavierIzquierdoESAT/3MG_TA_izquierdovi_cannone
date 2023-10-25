#include <cassert>
#include <memory>
#include <optional>
#include <tuple>
#include <typeinfo>
#include <unordered_map>
#include <vector>

struct Position {};

struct Physics {
  float acceleration;
};

struct Material {};

struct component_base {
  virtual void addComponent(unsigned e) = 0;
  virtual void removeComponent(unsigned e) = 0;
};

template <typename T>
struct component_list : component_base {
  void addComponent(unsigned e) override {
    if (e >= components_.size()) {
      components_.emplace_back(std::optional<T>);
    }
  }
  void removeComponent(unsigned e) override { components_[e].reset(); }
  // void setComponent(unsigned e, T c) override {
  //  components_
  //  components_.emplace_back(std::optional<T>);
  //}

  std::vector<std::optional<T>> components_;
};

class ComponentManager {
 public:
  std::unordered_map<std::size_t, std::unique_ptr<component_base>> components_;

  ComponentManager() {
    add_component_class<Position>();
    add_component_class<Physics>();
    add_component_class<Material>();
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

  template <typename T>
  void setComponent(unsigned e, T c) {
    auto comp_base = components_.find(typeid(T).hash_code());
    component_list<T> component_vector =
        static_cast <component_list<T>>(comp_base->second);
    component_vector.components_[e - 1] = c;
  }

  void deleteEntity(unsigned e) {
    for (auto& it : components_) {
      it.second->removeComponent(e);
    }
    freed.push_back(e);
  }

  std::vector<unsigned> freed;

 private:
  unsigned current_entity = 1;
  // Previous code
  //	std::vector<std::unique_ptr<component_base>> components_;

  // std::tuple<Position*,Physics*,Material*> get_entity(unsigned int e);
  // unsigned int new_entity(std::optional<Position> p = std::nullopt,
  // std::optional<Physics> ph = std::nullopt, std::optional<Material> m =
  // std::nullopt);
};

// Previous code
// std::tuple<Position*, Physics*, Material*>
// ComponentManager::get_entity(unsigned int e) { 	assert(e); 	e = e -
// 1; 	return {
// position[e].has_value() ? &position[e].value() : nullptr,
//		physics[e].has_value() ? &physics[e].value() : nullptr,
//		material[e].has_value() ? &material[e].value() : nullptr };
//}
//
// unsigned int ComponentManager::new_entity(std::optional<Position> p,
// std::optional<Physics> ph, std::optional<Material> m) {
// position.push_back(p);
//	physics.push_back(ph);
//	material.push_back(m);
//
//	return position.size();
//}

void physics_system(std::vector<std::optional<Position>>& positions,
                    std::vector<std::optional<Physics>>& physics) {
  auto p = positions.begin();
  auto ph = physics.begin();
  for (; p != positions.end(); p++, ph++) {
    if (!p->has_value() || !ph->has_value()) continue;
    auto& pv = p->value();
    auto& phv = ph->value();

    // Fisica dura
  }
  assert(ph == physics.end());
}

unsigned int entity;

struct ComponentLife {};

int main(int, char**) {
  ComponentManager component_manager;

  component_manager.add_component_class<ComponentLife>();

  // Previous code
  unsigned player = component_manager.addEntity();
  component_manager.deleteEntity(player);
  Position pos{};
  component_manager.setComponent<Position>(player, pos);

  std::vector<unsigned int> obstacles;
  for (int i = 0; i != 30; i++) {
    // Previous code
    // obstacles.push_back(component_manager.new_entity({}, {}, {}));
  }
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