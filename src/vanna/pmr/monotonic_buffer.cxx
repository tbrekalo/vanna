#include "vanna/pmr/monotonic_buffer.hpp"
#include "vanna/pmr/memory_resource.hpp"

namespace vanna {

namespace pmr {

void monotonic_buffer::release() noexcept {}

bool monotonic_buffer::do_is_equal(memory_resource const& rhs) const noexcept {
  return this == &rhs;
}

} // namespace pmr
} // namespace vanna