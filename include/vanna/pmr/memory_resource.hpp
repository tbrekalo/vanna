#ifndef VANNA_PMR_MEMORY_RESOURCE_HPP_
#define VANNA_PMR_MEMORY_RESOURCE_HPP_

#include <cstddef>
#include <cstdint>

namespace vanna {

namespace pmr {

class memory_resource {
public:
  using void_pointer = void*;
  using const_void_pointer = void const*;

  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  void_pointer allocate(size_type const n_bytes,
                        size_type const aling = alignof(std::max_align_t));

  void deallocate(void_pointer p, size_type const n_bytes,
                  size_type const align = alignof(std::max_align_t));

  bool is_equal(memory_resource const& rhs) const noexcept;

private:
  virtual void_pointer do_allocate(size_type const n_bytes,
                                   size_type const align) = 0;

  virtual void do_deallocate(void_pointer p, size_type const n_bytes,
                             size_type const align) = 0;

  virtual bool do_is_equal(memory_resource const& rhs) const noexcept = 0;
};

bool operator==(memory_resource const& lhs,
                memory_resource const& rhs) noexcept;

bool operator!=(memory_resource const& lhs,
                memory_resource const& rhs) noexcept;

} // namespace pmr
} // namespace vanna

#endif /* VANNA_PMR_MEMORY_RESOURCE_HPP_ */
