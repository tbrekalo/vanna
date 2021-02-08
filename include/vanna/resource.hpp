#ifndef VANNA_RESOURCE_HPP_
#define VANNA_RESOURCE_HPP_

#include <cstddef>

#include "vanna/byte.hpp"

namespace vanna {

class resource {
public:
  using size_type = std::size_t;

  byte_ptr_t allocate(size_type const n_bytes, size_type const alignment);
  void deallocate(byte_ptr_t p, size_type const n_bytes, size_type const alignemt);
  bool is_equal(resource const& rhs);

private:
  virtual byte_ptr_t do_allocate(size_type const n_bytes, size_type const alignment) = 0;
  virtual void do_deallocate(byte_ptr_t p, size_type const n_bytes, size_type const alignment) = 0;
  virtual bool do_is_equal(resource const& rhs) const noexcept = 0;
};

}

#endif /* VANNA_RESOURCE_HPP_ */