#include "vanna/detail/macro.hpp"
#include "vanna/new_delete.hpp"

#include <stdlib.h>
#include <new>

namespace vanna {

namespace detail {

byte_ptr aligned_new(std::size_t const n_bytes, std::size_t const align) {

#if defined(_WIN32) || defined(__CYGWIN__)
  auto const ptr = _aligned_malloc(n_bytes, align);
#elif defined(__APPLE__)
  auto const ptr = alloc(n_bytes);
#else
  auto const ptr = aligned_alloc(align, n_bytes);
#endif

  if (ptr == NULL) {
    throw std::bad_alloc();
  }

  return reinterpret_cast<byte_ptr>(ptr);
}

void aligned_free(byte_ptr ptr, std::size_t const align) {

  UNUSED(align);

#if defined(_WIN32) || defined(__CYGWIN__)
  _aligned_free(ptr);
#else
  free(ptr);
#endif
}

class new_delete : public resource {
public:
private:
  virtual pointer do_allocate(size_type const n_bytes, size_type const align);
  virtual void do_deallocate(pointer ptr, size_type const n_bytes,
                             size_type const align);
  virtual bool do_is_equal(resource const& rhs) const noexcept;
};

new_delete::pointer new_delete::do_allocate(size_type const n_bytes,
                                            size_type const align) {
  return aligned_new(n_bytes, align);
}

void new_delete::do_deallocate(pointer ptr, size_type const n_bytes,
                               size_type const align) {
  UNUSED(n_bytes);

  aligned_free(ptr, align);
}

bool new_delete::do_is_equal(resource const& rhs) const noexcept {
  return this == &rhs;
}

} // namespace detail

resource* get_new_delete() {
  static resource* instance = new detail::new_delete();
  return instance;
}


} // namespace vanna