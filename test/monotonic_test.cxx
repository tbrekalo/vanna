#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <set>

#include "catch2/catch.hpp"

#include "vanna/monotonic.hpp"
#include "vanna/allocator.hpp"

TEST_CASE("monotonic resource through allocator",
          "[vanna][monotonic][resource][allocator]") {
  using value_type = std::uint32_t;
  using alloc_type = vanna::allocator<value_type>;
  using container_type = std::vector<value_type, alloc_type>;

  auto constexpr type_size = sizeof(value_type);
  auto constexpr n_objects = 100;

  auto constexpr block_size = n_objects * type_size;

  vanna::monotonic resource(block_size);
  container_type container(&resource);
  container.reserve(n_objects);

  CHECK(container.capacity() == n_objects);

  for (value_type i = 0; i < n_objects; ++i) {
    container.push_back(i);
  }

  for (value_type i = 0; i < n_objects; ++i) {
    CHECK(container[i] == i);
  }
}