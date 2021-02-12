#ifndef VANNA_MONOTONIC_HPP_
#define VANNA_MONOTONIC_HPP_

#include "vanna/resource.hpp"
#include <cstddef>

namespace vanna {

class monotonic : public resource {
public:
  static size_type constexpr DEFAULT_BLOCK_CAPACITY = 1024;
  static double constexpr DEFAULT_GROWTH_FACTOR = 2;

  monotonic();
  monotonic(size_type const block_capacity);
  monotonic(size_type const block_capacity, double const growth_factor);

  monotonic(monotonic const&) = delete;
  monotonic& operator=(monotonic const&) = delete;

  monotonic(monotonic&& rhs) noexcept;
  monotonic& operator=(monotonic&& rhs) noexcept;

  void swap(monotonic& other);

private:
  struct block;
  using block_ptr = block*;

  struct block {
    block_ptr prev;
  };

  struct block_info {
    block_info(block_ptr const ptr, size_type const capacity)
        : ptr(ptr), capacity(capacity) {}

    block_ptr ptr;
    size_type capacity;
  };

  static auto constexpr BLOCK_OVERHEAD =
      sizeof(block) + (-sizeof(block) % alignof(std::max_align_t));

  block_info allocate_block(size_type const requested_capacity);
  void expand_block_list(size_type const requrest_capacity);

  pointer do_allocate(size_type const n_bytes, size_type const align) override;
  void do_deallocate(pointer ptr, size_type const n_bytes,
                     size_type const align) override;
  bool do_is_equal(resource const& rhs) const noexcept override;

  size_type block_capacity_;
  double growth_factor_;

  block_ptr curr_block_;
  size_type curr_block_sz_;
};

} // namespace vanna

#endif /* VANNA_MONOTONIC_HPP_ */