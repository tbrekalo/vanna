#include "vanna/new_delete.hpp"

namespace vanna {

class new_delete : public resource {
public:
private:
  virtual byte_ptr_t do_allocate(size_type const n_bytes,
                                 size_type const alignment) override;
  virtual void do_deallocate(byte_ptr_t p, size_type n_bytes,
                             size_type const alignment) override;
  virtual bool do_is_equal(resource const& rhs) const noexcept override;
};

resource* get_new_delete() {
  static auto instance = new_delete();
  return static_cast<resource*>(&instance);
}

byte_ptr_t new_delete::do_allocate(size_type const n_bytes,
                                   size_type const alignment) {

}

void new_delete::do_deallocate(byte_ptr_t p, size_type n_bytes,
                               size_type const alignment) {

                               }

bool new_delete::do_is_equal(resource const& rhs) const noexcept {
  return this == &rhs; // TODO: better? Runtime typeinfo
}

} // namespace vanna