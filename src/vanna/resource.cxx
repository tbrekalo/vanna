#include "vanna/resource.hpp"

namespace vanna {
  
byte_ptr_t resource::allocate(size_type const n_bytes, size_type const alignment) {
  return do_allocate(n_bytes, alignment);
}

void resource::deallocate(byte_ptr_t p, size_type const n_bytes, size_type const alignemt) {
  return do_deallocate(p, n_bytes, alignemt);
}

bool resource::is_equal(resource const& rhs) {
  return do_is_equal(rhs);
}


}