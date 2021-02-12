#include "vanna/monotonic.hpp"
#include "vanna/byte.hpp"

#include <algorithm>

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

monotonic::monotonic(monotonic&& rhs) noexcept
    : block_capacity_(0), growth_factor_(1), curr_block_(nullptr),
      curr_block_sz_(0) {
  swap(rhs);
}

monotonic& monotonic::operator=(monotonic&& rhs) noexcept {
  return *this = monotonic(std::move(rhs));
}

void monotonic::swap(monotonic& rhs) {
  std::swap(block_capacity_, rhs.block_capacity_);
  std::swap(growth_factor_, rhs.growth_factor_);

  std::swap(curr_block_, rhs.curr_block_);
  std::swap(curr_block_sz_, rhs.curr_block_sz_);
}

monotonic::block_info
monotonic::allocate_block(size_type const requested_capacity) {
  auto const block_size = requested_capacity + BLOCK_OVERHEAD;
  auto const mem_ptr =
      reinterpret_cast<block_ptr>(resource::allocate(requested_capacity, 1));

  return {mem_ptr, block_size};
}

void monotonic::expand_block_list(size_type const requested_capacity) {
  auto const info = allocate_block(requested_capacity * growth_factor_);
  auto const prev_block = curr_block_;

  curr_block_ = info.ptr;
  block_capacity_ = info.capacity;

  curr_block_->prev = prev_block;
  curr_block_sz_ = sizeof(block);
}

monotonic::pointer monotonic::do_allocate(size_type const n_bytes,
                                          size_type const align) {
  if ((-curr_block_sz_ % align) > block_capacity_ - curr_block_sz_) {
    expand_block_list(std::max(block_capacity_, n_bytes) * growth_factor_);
  }

  curr_block_sz_ += (-curr_block_sz_ % align);
  if (n_bytes > block_capacity_ - curr_block_sz_) {
    expand_block_list(std::max(block_capacity_, n_bytes) * growth_factor_);
    curr_block_sz_ += (-curr_block_sz_ % align);
  }

  auto const dst = reinterpret_cast<byte_ptr>(curr_block_) + curr_block_sz_;
  curr_block_sz_ += n_bytes;

  return dst;
}

void monotonic::do_deallocate(pointer ptr, size_type const n_bytes,
                              size_type const align) {}

bool monotonic::do_is_equal(resource const& rhs) const noexcept {
  return this == &rhs;
}

} // namespace vanna