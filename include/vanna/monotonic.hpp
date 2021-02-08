#ifndef VANNA_MONOTONIC_HPP_
#define VANNA_MONOTONIC_HPP_

#include "vanna/resource.hpp"

namespace vanna {

class monotonic : public resource {
public:
  static size_type constexpr GROWTH_FACTOR = 2;

  monotonic(size_type const block_capacity);
  void release();

  // TOOD: constructors and propagation properties
  ~monotonic();

private:
  struct block_t {
    block_t* prev;
  };

  using block_ptr_t = block_t*;

  struct block_info_t {
    block_info_t(block_ptr_t block_start, size_type n_bytes)
        : block_start(block_start), capacity(n_bytes) {}

    block_ptr_t block_start;
    size_type capacity;
  };

  block_info_t allocate_block(size_type block_capacity, size_type alignment);
  void append_new_block(block_info_t const info) noexcept;
  void expand_block_list(size_type const block_capacity,
                         size_type const alignment);

  virtual byte_ptr_t do_allocate(size_type const n_bytes,
                                 size_type const alignment) override;
  virtual void do_deallocate(byte_ptr_t p, size_type n_bytes,
                             size_type const alignment) override;
  virtual bool do_is_equal(resource const& rhs) const noexcept override;

  block_ptr_t curr_block_ = nullptr;

  size_type n_bytes_used_ = 0;
  size_type block_capacity_;
};

} // namespace vanna

#endif /* VANNA_MONOTONIC_HPP_ */