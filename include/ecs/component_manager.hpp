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
#include "ecs/component_lists.hpp"
#include "math/vector_2.h"
#include "math/vector_3.h"

/// @brief Abstracto for component usage
class ComponentManager {
 public:
  /// @brief
  ComponentManager();
  /// @brief non copyable
  ComponentManager(const ComponentManager&) = delete;

  ~ComponentManager() = default;

  template <typename... T>
  unsigned addEntity(T&... args) {
    unsigned e = addEntity();
    // loops throug the template arguments executing the lambda
    ([&] { setComponent(e, args); }(), ...);
    return e;
  }

  /// @brief deltes an Entity from the system
  /// @param e Entity to delete
  void deleteEntity(unsigned& e);

  /// @brief adds a custom component type to be used
  /// @tparam T compoennt type
  template <typename T>
  void addComponentClass(ComponentListType t) {
    if (t == ComponentListType::kSparse) {
      components_.emplace(typeid(T).hash_code(),
                          std::make_unique<ComponentListSparse<T>>());
    } else {
      components_.emplace(typeid(T).hash_code(),
                          std::make_unique<ComponentListCompact<T>>());
    }
  }

  /// @brief sets a component for the specified entity
  /// @tparam T component type
  /// @param e entity id
  /// @param c component to set
  template <typename T>
  void setComponent(unsigned e, T& c) {
    auto comp_base = components_.find(typeid(T).hash_code());
    if (comp_base->second.get()->type_ == ComponentListType::kSparse) {
      ComponentListSparse<T>* component_vector =
          static_cast<ComponentListSparse<T>*>(comp_base->second.get());
      component_vector->components_[e - 1].emplace(std::move(c));

    } else {
      ComponentListCompact<T>* component_vector =
          static_cast<ComponentListCompact<T>*>(comp_base->second.get());
      component_vector->setComponent(e, c);
    }
  }

  /// @brief retrieves a component for a specific entity
  /// @tparam T component type
  /// @param e entity
  /// @return specified component if found
  template <typename T>
  T* getComponent(unsigned e) {
    auto comp_base = components_.find(typeid(T).hash_code());
    if (comp_base->second.get()->type_ == ComponentListType::kSparse) {
      ComponentListSparse<T>* component_vector =
          static_cast<ComponentListSparse<T>*>(comp_base->second.get());
      return &component_vector->components_[e - 1].value();

    } else {
      ComponentListCompact<T>* component_vector =
          static_cast<ComponentListCompact<T>*>(comp_base->second.get());
      return component_vector->getComp(e);
    }
  }

  /// @brief retrieves complete component container
  /// @tparam T Component type
  /// @return container
  template <typename T>
  ComponentListCompact<T>& getCompactIterator() {
    auto comp_base = components_.find(typeid(T).hash_code());
    ComponentListCompact<T>* component_vector =
        static_cast<ComponentListCompact<T>*>(comp_base->second.get());
    return *component_vector;
  }

  /// @brief retrieves complete component container
  /// @tparam T Component type
  /// @return container
  template <typename T>
  ComponentListSparse<T>& getIterator() {
    auto comp_base = components_.find(typeid(T).hash_code());
    ComponentListSparse<T>* component_vector =
        static_cast<ComponentListSparse<T>*>(comp_base->second.get());
    return *component_vector;
  }

  /// @brief retrieves all the components of the specified type
  /// @tparam T component type
  /// @return all T components
  template <typename T>
  std::vector<std::optional<T>>& getAll() {
    auto comp_base = components_.find(typeid(T).hash_code());
    ComponentListSparse<T>* component_vector =
        static_cast<ComponentListSparse<T>*>(comp_base->second.get());
    return component_vector->components_;
  }

 private:
  /// @brief creates an entity with no components the needed components for the
  /// entity must be inserted using setComponent
  /// @return entity id
  unsigned addEntity();

  // map containint all component lists
  std::unordered_map<std::size_t, std::unique_ptr<ComponentListBase>>
      components_;

  // marks the positions where entities have been freed so that they can be
  // filled with new components to avoid blanks in the compoent vectors
  std::vector<unsigned> freed_entities_;

  // biggest entity id or position in the array
  unsigned current_entity_;
};