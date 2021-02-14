#include "vanna/new_delete.hpp"
#include "vanna/default.hpp"
#include "vanna/resource.hpp"

#include <atomic>

namespace vanna {
namespace detail {

std::atomic<resource*> instance(get_new_delete());

}

resource* get_default_resource() {
  return detail::instance.load();
}

resource* set_default_resource(resource* r) {
  return detail::instance.exchange(r);
}

} // namespace vanna