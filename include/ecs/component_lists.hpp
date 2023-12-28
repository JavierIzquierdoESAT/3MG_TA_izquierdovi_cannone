#pragma once


/// @brief type of container
enum class ComponentListType {
  kCompact,  ///< for compoenents used by few entities
  kSparse    ///< for compnents that are used by most entities
};

/// @brief Interface for the different Component containers
class ComponentListBase {
public:
  friend class ComponentManager;

  /// @brief
  /// @param t
  ComponentListBase(ComponentListType t) : type_{t} {}

  /// @brief type of container used
  const ComponentListType type_;

  virtual ~ComponentListBase() = default;

protected:
  /// @brief performs needed operations on the container when adding entities 
  /// to the program
  /// @param e entity id
  /// @return true if the opertions were succesful
  virtual bool addEntity(unsigned e) = 0;

  /// @brief performs needed operations on the container when deleting entities
  /// @param e entity id
  /// @return true if the opertions were succesful
  virtual bool removeComponent(unsigned e) = 0;
};

template <typename T>
class ComponentList : public ComponentListBase {
public:
  ComponentList(ComponentListType t) : ComponentListBase(t) {}
};

/// @brief Container for compnents that are used by most entities
/// 
/// all of these containers will have the same size, wich will be number of
/// entities, this means that there will be a blank for entities that dont use 
/// this component type, wasting performance when iterating them
/// @tparam T Component to store
template <typename T>
class ComponentListSparse : public ComponentList<T> {
public:
  friend class ComponentManager;
  ComponentListSparse() : ComponentList<T>(ComponentListType::kSparse) {}
  using ComponentType = T;
  /// @brief provides an stardat way of iterating the container
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::optional<T>;
    using pointer = std::optional<T>*;    // or also value_type*
    using reference = std::optional<T>&;  // or also value_type&

    Iterator(pointer ptr, unsigned pos) : m_ptr_(ptr), pos_(pos) {}

    reference operator*() const { return *m_ptr_; }
    pointer operator->() { return m_ptr_; }

    Iterator& operator++() {
      ++m_ptr_;
      ++pos_;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      ++this->pos_;
      return tmp;
    }
    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.m_ptr_ == b.m_ptr_;
    };
    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return a.m_ptr_ != b.m_ptr_;
    };

    unsigned pos() const { return pos_; };
    bool valid() {
      return m_ptr_->has_value();
    }
    T& component() const {
      return m_ptr_->value();
    }

  private:
    pointer m_ptr_;
    unsigned pos_;
  };

  Iterator begin() {
    return Iterator(&components_[0], 1);
  };
  Iterator at(unsigned e) {
    return Iterator(&components_.at(e - 1),
                    e);
  }
  Iterator end() {
    auto it = Iterator(&components_[components_.size() - 1],
                       static_cast<unsigned>(components_.size()));
    ++it;
    return it;
  }

private:
  bool addEntity(unsigned e) override {
    if (e >= components_.size()) {
      components_.emplace_back(std::optional<T>());
      return true;
    }
    return false;
  }
  bool removeComponent(unsigned e) override {
    if (e > 0 && e < components_.size()) {
      components_[e - 1].reset();
      return true;
    }
    return false;
  }
  std::vector<std::optional<T>> components_;
};

/// @brief Container for compoenents used by few entities
/// 
/// this container has a slower access to each of component while iterating 
/// throug them, but elements will always have a component
/// @tparam T Component to store
template <typename T>
class ComponentListCompact : public ComponentList<T> {
public:
  friend class ComponentManager;
  ComponentListCompact() : ComponentList<T>(ComponentListType::kCompact) {}
  using ComponentType = T;
  /// @brief provides an stardat way of iterating the container
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<unsigned, T>;
    using pointer = std::pair<unsigned, T>*;
    using reference = std::pair<unsigned, T>&;

    Iterator(pointer ptr, bool ends = false) : m_ptr_(ptr), valid_{!ends} {}

    reference operator*() const { return *m_ptr_; }
    pointer operator->() { return m_ptr_; }

    Iterator& operator++() {
      ++m_ptr_;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.m_ptr_ == b.m_ptr_;
    }
    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return a.m_ptr_ != b.m_ptr_;
    }
    int pos() const {
      return m_ptr_->first;
    }
    bool valid() const {
      return valid_;
    }
    T& component() const {
      return m_ptr_->second;
    }

  private:
    pointer m_ptr_;
    bool valid_;
  };

  /// @brief get the first element of the container
  /// @return iterator
  Iterator begin() {
    return Iterator(&components_[0]);
  }

  /// @brief get the component of a specific entity
  /// @param e entity to retrieve the component from
  /// @return iterator or end() if not found
  Iterator at(unsigned e) {
    // TODO: possible bug converting form vector iterator to ComponentListCompact
    auto lb =
        std::lower_bound(components_.begin(), components_.end(), e, compare);

    size_t pos = lb - components_.begin();
    if (lb->first == e)
      return Iterator(&components_.at(pos));
    return end();
  }
  /// @brief get the last element + 1 (the element cannot be used)
  /// @return iterator
  Iterator end() {
    auto it = Iterator(
        &components_[static_cast<unsigned>(components_.size()) - 1], true);
    ++it;
    return it;
  }

private:
  static bool compare(std::pair<unsigned, T>& x, unsigned e) {
    return x.first < e;
  }

  // does nothing since it doesn't have to insert emptys for each entity
  bool addEntity(unsigned) override { return false; }

  // if the entity doesn't exist inserts a new pair
  bool setComponent(unsigned e, T& c) {
    auto lb =
        std::lower_bound(components_.begin(), components_.end(), e, compare);
    if (lb == components_.end()) {
      components_.emplace_back(std::make_pair(e, std::move(c)));
      return true;
    } else if (lb->first != e) {
      components_.insert(lb, std::make_pair(e, std::move(c)));
      return true;
    }
    return false;
  }

  // deletes a specific components if exists
  bool removeComponent(unsigned e) override {
    auto lb =
        std::lower_bound(components_.begin(), components_.end(), e, compare);
    if (lb->first == e) {
      components_.erase(lb);
      return true;
    }
    return false;
  }

  T* getComp(unsigned e) {
    auto lb =
        std::lower_bound(components_.begin(), components_.end(), e, compare);
    if (lb->first == e) return &lb->second;
    return nullptr;
  }

  std::vector<std::pair<unsigned, T>> components_;
};

template <typename T, typename... Types>
class ComponentIterator {
public:
  ComponentIterator(T& main, Types&... list)
    : lists_(std::make_tuple(&list...)),
      main_list_(&main),
      main_it_(main.begin()) {}

  static bool allExists(auto&... lists) {
    return (true && ... && lists->at(main_it_.pos()).valid());
  }
  bool next() {
    auto all_exist = [this](auto&... lists) -> bool {
      return (true && ... && lists->at(main_it_.pos()).valid());
    };
    auto it_end = main_list_->end();

    while (main_it_ != it_end) {
      if (main_it_.valid()) {
        if (std::apply(all_exist, lists_)) {
          return true;
        }
      }
      ++main_it_;
    }
    return false;
  }
  auto get() {
    auto res = std::apply(
        [this](auto&... lists) {
          return std::make_tuple(std::ref(main_it_.component()),
                                 std::ref(lists->at(main_it_.pos()).component())
                                 ...);
        },
        lists_);
    ++main_it_;
    return res;
  }

private:
  std::tuple<Types*...> lists_;
  T* main_list_;
  typename T::Iterator main_it_;
};
