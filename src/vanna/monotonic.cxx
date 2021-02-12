#include "vanna/monotonic.hpp"
#include "vanna/default.hpp"

#include <algorithm>
#include <cstddef>
#include <memory>

namespace vanna {

monotonic::monotonic() : monotonic(get_default(), DEFAULT_BUFF_SZ) {}

monotonic::monotonic(resource* const upstream)
    : monotonic(upstream, DEFAULT_BUFF_SZ) {}

monotonic::monotonic(size_type const block_capacity)
    : monotonic(get_default(), DEFAULT_BUFF_SZ) {}

monotonic::monotonic(resource* upstream, size_type const block_capacity)
    : upstream_(upstream) {
  expand_block_list(block_capacity, alignof(std::max_align_t));
}

monotonic::block_info_t monotonic::allocate_block(size_type block_capacity,
                                                  size_type alignment) {
  if (alignment < alignof(std::max_align_t)) {
    alignment = alignof(std::max_align_t);
  }

  auto const capacity = block_capacity + (-block_capacity_ % alignment);
  auto const block_start =
      reinterpret_cast<block_ptr_t>(upstream_->allocate(capacity, alignment));

  return block_info_t(block_start, capacity);
}

void monotonic::append_new_block(block_info_t const info) noexcept {
  auto const prev_block = curr_block_;

  curr_block_ = info.block_start;
  block_capacity_ = info.capacity;

  curr_block_->prev = prev_block;
  n_bytes_used_ = sizeof(block_t);
}

void monotonic::expand_block_list(size_type const block_capacity,
                                  size_type const alignment) {
  append_new_block(allocate_block(block_capacity, alignment));
}

monotonic::~monotonic() { release(); }

void monotonic::release() {
  for (block_ptr_t block = curr_block_; block != nullptr;) {
    auto next_block = block->prev;
    ::operator delete(block);

    block = next_block;
  }
}

byte_ptr_t monotonic::do_allocate(size_type const n_bytes,
                                  size_type const alignment) {

  if ((-n_bytes_used_ % alignment) > block_capacity_ - n_bytes_used_) {
    expand_block_list(
        std::max(block_capacity_ * GROWTH_FACTOR, n_bytes * GROWTH_FACTOR),
        alignment);
  }

  n_bytes_used_ += (-n_bytes_used_ % alignment);
  if (n_bytes > block_capacity_ - n_bytes_used_) {
    expand_block_list(
        std::max(block_capacity_ * GROWTH_FACTOR, n_bytes * GROWTH_FACTOR),
        alignment);
    n_bytes_used_ += (n_bytes_used_ % alignment);
  }

  auto const dst = reinterpret_cast<byte_ptr_t>(curr_block_) + n_bytes;
  n_bytes_used_ += n_bytes;

  return dst;
}

void monotonic::do_deallocate(byte_ptr_t p, size_type const n_bytes,
                              size_type const alignemnt) {
  // does nothing
}

bool monotonic::do_is_equal(resource const& rhs) const noexcept {
  return this == &rhs;
}

} // namespace vanna
