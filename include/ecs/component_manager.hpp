#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <optional>
#include <tuple>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "buffer.hpp"
#include "default_components.hpp"
#include "math/vector_2.h"
#include "math/vector_3.h"

struct component_list_base {
  virtual void addComponent(unsigned e) = 0;
  virtual void removeComponent(unsigned e) = 0;
};

template <typename T>
struct component_list : component_list_base {
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
  /// @brief
  ComponentManager();
  /// @brief non copyable
  ComponentManager(const ComponentManager&) = delete;

  ~ComponentManager() = default;

  /// @brief creates an entity with no components the needed components for the
  /// entity must be inserted using setComponent
  /// @return entity id
  unsigned addEntity();

  /// @brief creates and enity and intializes it's components to represent a
  /// triangle
  /// @return entity id
  unsigned addTriangle(float size, class ShaderManager* sm, Vec3 color);
  void deleteEntity(unsigned& e);

  /// @brief adds a custom component type to be used
  /// @tparam T compoennt type
  template <typename T>
  void add_component_class() {
    components_.emplace(typeid(T).hash_code(),
                        std::make_unique<component_list<T>>());
  }

  /// @brief sets a component for the specified entity
  /// @tparam T component type
  /// @param e entity id
  /// @param c component to set
  template <typename T>
  void setComponent(unsigned e, T&& c) {
    auto comp_base = components_.find(typeid(T).hash_code());
    component_list<T>* component_vector =
        static_cast<component_list<T>*>(comp_base->second.get());
    component_vector->components_[e - 1].emplace(std::move(c));
  }

  /// @brief retrieves a component for a specific entity
  /// @tparam T component type
  /// @param e entity
  /// @return specified component if found
  template <typename T>
  T* getComponent(unsigned e) {
    auto comp_base = components_.find(typeid(T).hash_code());
    component_list<T>* component_vector =
        static_cast<component_list<T>*>(comp_base->second.get());
    return &component_vector->components_[e - 1].value();
  }

  /// @brief retrieves all the components of the specified type
  /// @tparam T component type
  /// @return all T components
  template <typename T>
  std::vector<std::optional<T>>& getAll() {
    auto comp_base = components_.find(typeid(T).hash_code());
    component_list<T>* component_vector =
        static_cast<component_list<T>*>(comp_base->second.get());
    return component_vector->components_;
  }

 private:
  // map containint all component lists
  std::unordered_map<std::size_t, std::unique_ptr<component_list_base>>
      components_;

  // marks the positions where entities have been freed so that they can be
  // filled with new components to avoid blanks in the compoent vectors
  std::vector<unsigned> freed_entities_;

  // biggest entity id or position in the array
  unsigned current_entity_;
};