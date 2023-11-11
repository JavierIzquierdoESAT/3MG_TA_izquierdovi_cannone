#pragma once

class component_list_base {
 public:
  friend class ComponentManager;

 protected:
  virtual void addComponent(unsigned e) = 0;
  virtual void removeComponent(unsigned e) = 0;
};

template <typename T>
class ComponentList : public component_list_base {
 public:
  friend class ComponentManager;
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
