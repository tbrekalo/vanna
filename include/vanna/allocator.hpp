#ifndef VANNA_ALLOCATOR_HPP_
#define VANNA_ALLOCATOR_HPP_

#include <type_traits>
#include <cstddef>

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
  using propagate_on_container_move_assignment = std::false_type;
  using propagate_on_container_swap = std::true_type;

  template <class U>
  struct rebind {
    using other = allocator<U>;
  };

  template <class U>
  constexpr allocator(allocator<U> const& rhs) noexcept 
    : upstream_(rhs.upstream()) {}

  allocator(resource* const upstream) : upstream_(upstream) {}

  allocator(allocator const& rhs) { upstream_ = rhs.upstream_; }
  allocator& operator=(allocator const&) = delete;

  allocator(allocator&& rhs) : upstream_(nullptr) { swap(rhs); }
  allocator& operator=(allocator&&) = delete;

  void swap(allocator& rhs) { std::swap(upstream_, rhs.upstream_); }

  pointer allocate(size_type const n_objects) {
    return reinterpret_cast<pointer>(
        upstream_->allocate(bytes * n_objects, align));
  }

  void deallocate(pointer p, size_type const n_bytes) {
    upstream_->deallocate(reinterpret_cast<resource::pointer>(p), n_bytes,
                          align);
  }

  resource* upstream() const noexcept { return upstream_; }

private:
  resource* upstream_;
};

template <class LhsT, class RhsT>
bool operator==(allocator<LhsT> const& lhs,
                allocator<RhsT> const& rhs) noexcept {
  return lhs.upstream()->is_equal(rhs.upstream());
}

template <class LhsT, class RhsT>
bool operator!=(allocator<LhsT> const& lhs,
                allocator<RhsT> const& rhs) noexcept {
  return !(lhs == rhs);
}

} // namespace vanna

#endif /* VANNA_ALLOCATOR_HPP_ */