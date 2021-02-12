#ifndef VANNA_ALLOCATOR_HPP_
#define VANNA_ALLOCATOR_HPP_

#include <cstddef>
#include <type_traits>

#include "vanna/resource.hpp"

namespace vanna {

template <class T = byte>
class allocator {
public:
  using value_type = T;

  using pointer = value_type*;
  using const_pointer = value_type const*;

  using size_type = resource::size_type;
  using difference_type = std::ptrdiff_t;

private:
  static auto constexpr align = alignof(value_type);
  static auto constexpr bytes = sizeof(value_type);

public:
  // Influence on container operations
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;

  template <class U>
  struct rebind {
    using other = allocator<U>;
  };

  allocator(resource* const upstream) : upstream_(upstream) {}

  pointer allocate(size_type const n_objects) {
    return upstream_->allocate(bytes * n_objects, align);
  }

  void deallocate(pointer p, size_type const n_bytes) {
    upstream_->deallocate(p, n_bytes, align);
  }

private:
  resource* upstream_;
};

} // namespace vanna

#endif /* VANNA_ALLOCATOR_HPP_ */