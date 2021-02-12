#include "vanna/new_delete.hpp"
#include "vanna/resource.hpp"

#include <atomic>

namespace vanna {

namespace detail {

std::atomic<resource*> ptr(get_new_delete());

}

resource* get_default() {
  return detail::ptr.load();
}

void set_default(resource* ptr) {
  detail::ptr.store(ptr);
}

}