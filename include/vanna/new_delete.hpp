#ifndef VANNA_NEW_DELETE_HPP_
#define VANNA_NEW_DELETE_HPP_

#include "vanna/resource.hpp"
namespace vanna {

class new_delete : public resource {
public:
private:
  virtual pointer do_allocate(size_type const n_bytes, size_type const align);
  virtual void do_deallocate(pointer ptr, size_type const n_bytes,
                             size_type const align);
  virtual bool do_is_equal(resource const& rhs) const noexcept;
};

} // namespace vanna

#endif /* VANNA_NEW_DELETE_HPP_ */