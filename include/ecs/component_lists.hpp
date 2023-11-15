#pragma once

enum class ComponentListType { kCompact, kSparse };

class componentListBase {
 public:
  friend class ComponentManager;

  componentListBase(ComponentListType t) : type_{t} {}
  const ComponentListType type_;

 protected:
  virtual void addComponent(unsigned e) = 0;
  virtual void removeComponent(unsigned e) = 0;
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
  void addComponent(unsigned e) override {
    if (e >= components_.size()) {
      components_.emplace_back(std::optional<T>());
    }
  }
  void removeComponent(unsigned e) override { components_[e - 1].reset(); }
  std::vector<std::optional<T>> components_;
};

template <typename T>
class ComponentListCompact : public componentListBase {
 public:
  friend class ComponentManager;
  ComponentListCompact() : componentListBase(ComponentListType::kCompact) {}

 private:
  void addComponent(unsigned e) override {}
  void removeComponent(
      unsigned e) override { /*components_.erase(getIndex(e));*/
  }

  std::vector<std::pair<unsigned, T>>::iterator getIndex(unsigned e) {
    //return components_.begin();
    // TODO: Make this shit work
    
     return std::lower_bound(
        components_.begin(), components_.end(), e,
        [](const std::vector<std::pair<unsigned, T>>::value_type& x,
           unsigned e) {
          return x.first < e;
        });
  }

  T& getComp(unsigned e) { return getIndex(e)->second; }

  std::vector<std::pair<unsigned, T>> components_;
};