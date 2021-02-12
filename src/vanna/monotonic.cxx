#include "vanna/detail/macro.hpp"
#include "vanna/monotonic.hpp"
#include "vanna/byte.hpp"

#include <algorithm>
#include <cstddef>

namespace vanna {

monotonic::monotonic()
    : monotonic(DEFAULT_BLOCK_CAPACITY, DEFAULT_GROWTH_FACTOR) {}

monotonic::monotonic(size_type const block_capacity)
    : monotonic(block_capacity, DEFAULT_GROWTH_FACTOR) {}

monotonic::monotonic(size_type const block_capacity, double const growth_factor)
    : growth_factor_(growth_factor) {

  curr_block_ = nullptr;
  expand_block_list(block_capacity);
}

void monotonic::swap(monotonic& rhs) {
  std::swap(growth_factor_, rhs.growth_factor_);

  std::swap(curr_block_, rhs.curr_block_);
  std::swap(curr_block_sz_, rhs.curr_block_sz_);
}

monotonic::~monotonic() { release(); }

void monotonic::release() {
  auto curr_block = curr_block_;
  while (curr_block != nullptr) {
    auto to_delete = curr_block;
    curr_block = curr_block->prev;

    // TODO: setup upstream
    // resource::deallocate(reinterpret_cast<byte_ptr>(curr_block),
    //                      curr_block->capacity, alignof(block));
    ::operator delete(to_delete);
  }
}

monotonic::block_ptr
monotonic::allocate_block(size_type const requested_capacity) {
  auto const block_capacity = requested_capacity + BLOCK_OVERHEAD;

  auto const mem_ptr =
      reinterpret_cast<block_ptr>(::operator new(block_capacity));

  mem_ptr->capacity = block_capacity;
  return mem_ptr;
}

void monotonic::expand_block_list(size_type const requested_capacity) {
  auto const new_block = allocate_block(requested_capacity * growth_factor_);
  auto const prev_block = curr_block_;

  curr_block_ = new_block;

  curr_block_->prev = prev_block;
  curr_block_sz_ = sizeof(block);
}

monotonic::pointer monotonic::do_allocate(size_type const n_bytes,
                                          size_type const align) {
  if ((-curr_block_sz_ % align) > curr_block_->capacity - curr_block_sz_) {
    expand_block_list(std::max(curr_block_->capacity, n_bytes) *
                      growth_factor_);
  }

  curr_block_sz_ += (-curr_block_sz_ % align);
  if (n_bytes > curr_block_->capacity - curr_block_sz_) {
    expand_block_list(std::max(curr_block_->capacity, n_bytes) *
                      growth_factor_);

    curr_block_sz_ += (-curr_block_sz_ % align);
  }

  auto const dst = reinterpret_cast<byte_ptr>(curr_block_) + curr_block_sz_;
  curr_block_sz_ += n_bytes;

  return dst;
}

void monotonic::do_deallocate(pointer ptr, size_type const n_bytes,
                              size_type const align) {
  UNUSED(ptr);
  UNUSED(align);
  UNUSED(n_bytes);
}

bool monotonic::do_is_equal(resource const& rhs) const noexcept {
  return this == &rhs;
}

} // namespace vanna