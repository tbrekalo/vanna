#include "vanna/pmr/memory_resource.hpp"

namespace vanna {

namespace pmr {

memory_resource::void_pointer memory_resource::allocate(size_type const n_bytes,
                                                        size_type const align) {
  return do_allocate(n_bytes, align);
}

void memory_resource::deallocate(void_pointer p, size_type const n_bytes,
                                 size_type const align) {
  return do_deallocate(p, n_bytes, align);
}

bool memory_resource::is_equal(memory_resource const& rhs) const noexcept {
  return do_is_equal(rhs);
}

bool operator==(memory_resource const& lhs,
                memory_resource const& rhs) noexcept {
  return &lhs == &rhs || lhs.is_equal(rhs);
}

bool operator!=(memory_resource const& lhs,
                memory_resource const& rhs) noexcept {
  return !(lhs == rhs);
}

} // namespace pmr
} // namespace vanna