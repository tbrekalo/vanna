#ifndef VANNA_PMR_MONOTONIC_BUFFER_HPP_
#define VANNA_PMR_MONOTONIC_BUFFER_HPP_

#include "vanna/pmr/memory_resource.hpp"

namespace vanna {

namespace pmr {

class monotonic_buffer : memory_resource {
public:
  void release() noexcept;

private:
  struct header_t {
    header_t* prev;
  };

  header_t* curr_buff_;
  size_type curr_buff_size_;
  size_type curr_buff_capacity_;

  void_pointer do_allocate(size_type const n_bytes,
                           size_type const align) override;
  void do_deallocate(void_pointer p, size_type const n_bytes,
                     size_type const align) override;
  bool do_is_equal(memory_resource const& rhs) const noexcept override;
};

} // namespace pmr
} // namespace vanna

#endif /* VANNA_PMR_MONOTONIC_BUFFER_HPP_ */