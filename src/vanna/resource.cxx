#include "vanna/resource.hpp"
#include "vanna/detail/macro.hpp"

#include <stdlib.h>
#include <new>

namespace vanna {

namespace detail {

byte_ptr aligned_new(std::size_t const n_bytes, std::size_t const align) {
#if defined(_WIN32) || defined(__CYGWIN__)
  auto const ptr = _aligned_malloc(n_bytes, align);
#else
  auto const ptr = aligned_alloc(align, n_bytes);
#endif

  if (ptr == NULL) {
    throw std::bad_alloc();
  }

  return static_cast<byte_ptr>(ptr);
}

void aligned_free(byte_ptr ptr, std::size_t const align) {

  UNUSED(align);

#if defined(_WIN32) || defined(__CYGWIN__)
  _aligned_free(ptr);
#else
  free(ptr);
#endif
}

} // namespace detail

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

resource::pointer resource::do_allocate(size_type const n_bytes,
                                        size_type const align) {
  return detail::aligned_new(n_bytes, align);
}

void resource::do_deallocate(pointer ptr, size_type const n_bytes,
                             size_type const align) {
  UNUSED(n_bytes);

  detail::aligned_free(ptr, align);
}

bool resource::do_is_equal(resource const& rhs) const noexcept {
  return this == &rhs;
}

} // namespace vanna