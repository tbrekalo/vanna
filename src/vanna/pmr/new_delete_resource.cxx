#include "vanna/pmr/new_delete_resource.hpp"
#include "vanna/pmr/memory_resource.hpp"

#include <new>

namespace vanna {
namespace pmr {
namespace detail {

class new_delete_resource : public memory_resource {
private:
  void_pointer do_allocate(size_type const n_bytes,
                           size_type const align) override {
    return ::operator new(n_bytes);
  }

  void do_deallocate(void_pointer p, size_type const n_bytes,
                     size_type const align) override {
    return ::operator delete(p);
  }

  bool do_is_equal(memory_resource const& rhs) const noexcept override {
    return this == &rhs;
  }
};

} // namespace detail

memory_resource* new_delete_resource() noexcept {
  static auto instance = detail::new_delete_resource();
  return &instance;
}

} // namespace pmr
} // namespace vanna