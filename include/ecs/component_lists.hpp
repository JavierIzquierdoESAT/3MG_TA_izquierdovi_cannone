#pragma once

enum class ComponentListType { kCompact, kSparse };

class componentListBase {
 public:
  friend class ComponentManager;

  componentListBase(ComponentListType t) : type_{t} {}
  const ComponentListType type_;

 protected:
  virtual bool addEntity(unsigned e) = 0;
  virtual bool removeComponent(unsigned e) = 0;
};

template <typename T>
class ComponentList : public componentListBase {
 public:
  friend class ComponentManager;
  ComponentList() : componentListBase(ComponentListType::kSparse) {}

  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::optional<T>;
    using pointer = std::optional<T>*;    // or also value_type*
    using reference = std::optional<T>&;  // or also value_type&

    Iterator(pointer ptr) : m_ptr_(ptr) {}

    reference operator*() const { return *m_ptr_; }
    pointer operator->() { return m_ptr_; }

    Iterator& operator++() {
      m_ptr_++;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.m_ptr_ == b.m_ptr_;
    };
    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return a.m_ptr_ != b.m_ptr_;
    };

   private:
    pointer m_ptr_;
  };

  Iterator begin() { return Iterator(&components_[0]); };
  Iterator end() {
    auto it = Iterator(&components_[components_.size() - 1]);
    it++;
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

template <typename T>
class ComponentListCompact : public componentListBase {
 public:
  friend class ComponentManager;
  ComponentListCompact() : componentListBase(ComponentListType::kCompact) {}

  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<unsigned, T>;
    using pointer = std::pair<unsigned, T>*;
    using reference = std::pair<unsigned, T>&;

    Iterator(pointer ptr) : m_ptr_(ptr) {}

    reference operator*() const { return *m_ptr_; }
    pointer operator->() { return m_ptr_; }

    Iterator& operator++() {
      m_ptr_++;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.m_ptr_ == b.m_ptr_;
    };
    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return a.m_ptr_ != b.m_ptr_;
    };

   private:
    pointer m_ptr_;
  };

  Iterator begin() { return Iterator(&components_[0]); };
  Iterator end() {
    auto it = Iterator(&components_[components_.size() - 1]);
    it++;
    return it;
  }
 private:
  static bool compare(std::pair<unsigned, T>& x, unsigned e) {
    return x.first < e;
  }

  // does nothing since it doesn't have to insert emptys for each entity
  bool addEntity(unsigned e) override {return false;}

  // if the entity doesn't exist inserts a new pair
  bool setComponent(unsigned e, T& c) {
    if (components_.size()) {
      auto lb =
          std::lower_bound(components_.begin(), components_.end(), e, compare);
      if (lb->first == e) return false;
      components_.insert(lb--, std::make_pair(e, std::move(c)));
    } else {
      components_.emplace_back(std::make_pair(e, std::move(c)));
    }
    return true;

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