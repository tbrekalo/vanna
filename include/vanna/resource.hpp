#ifndef VANNA_RESOURCE_HPP_
#define VANNA_RESOURCE_HPP_

#include "vanna/byte.hpp"

#include <cstddef>

namespace vanna {

class resource {
public:
  using size_type = std::size_t;
  using pointer = byte_ptr;

  pointer allocate(size_type const n_bytes, size_type const align);
  void deallocate(pointer ptr, size_type const n_bytes, size_type const align);
  bool is_equal(resource const& rhs) const noexcept;

private:
  virtual pointer do_allocate(size_type const n_bytes, size_type const align) = 0;
  virtual void do_deallocate(pointer ptr, size_type const n_bytes,
                             size_type const align) = 0;
  virtual bool do_is_equal(resource const& rhs) const noexcept = 0;
};

} // namespace vanna

#endif /* VANNA_RESOURCE_HPP_ */