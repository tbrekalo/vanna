#include "vanna/resource.hpp"
#include "vanna/detail/macro.hpp"

namespace vanna {

resource::pointer resource::allocate(size_type const n_bytes,
                                     size_type const align) {
  return do_allocate(n_bytes, align);
}

void resource::deallocate(pointer ptr, size_type const n_bytes,
                          size_type const align) {
  return do_deallocate(ptr, n_bytes, align);
}

bool resource::is_equal(resource const& rhs) const noexcept {
  return do_is_equal(rhs);
}

} // namespace vanna