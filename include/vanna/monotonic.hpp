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
  monotonic(resource* upstream);
  monotonic(size_type const block_capacity);
  monotonic(resource* upstream, size_type const block_capacity);
  monotonic(resource* upstream, size_type const block_capacity, double const growth_factor);

  ~monotonic();
  void release();

  monotonic(monotonic const&) = delete;
  monotonic& operator=(monotonic const&) = delete;

  monotonic(monotonic&&) = delete;
  monotonic& operator=(monotonic&&) = delete;

  void swap(monotonic& other);

private:
  struct block;
  using block_ptr = block*;

  struct block {
    block_ptr prev;
    size_type capacity;
  };

  static auto constexpr BLOCK_OVERHEAD =
      sizeof(block) + (-sizeof(block) % alignof(block));

  block_ptr allocate_block(size_type const requested_capacity);
  void expand_block_list(size_type const requrest_capacity);

  pointer do_allocate(size_type const n_bytes, size_type const align) override;
  void do_deallocate(pointer ptr, size_type const n_bytes,
                     size_type const align) override;
  bool do_is_equal(resource const& rhs) const noexcept override;

  resource* upstream_;

  double growth_factor_;

  block_ptr curr_block_;
  size_type curr_block_sz_;
};

} // namespace vanna

#endif /* VANNA_MONOTONIC_HPP_ */