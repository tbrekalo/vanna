#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "catch2/catch.hpp"

#include "vanna/monotonic.hpp"
#include "vanna/allocator.hpp"

// TODO: better test parametrization, TypeList as a zip on types?

TEMPLATE_TEST_CASE("resource through allocator, std::vector",
                   "[vanna][monotonic][resource][allocator][std::vector][stl]",
                   vanna::monotonic) {
  using value_type = std::uint32_t;
  using alloc_type = vanna::allocator<value_type>;
  using container_type = std::vector<value_type, alloc_type>;
  using resource_type = TestType;

  auto constexpr n_objects = 1000;

  resource_type resource{};
  container_type container(&resource);
  container.reserve(n_objects);

  CHECK(container.capacity() == n_objects);

  for (value_type i = 0; i < n_objects; ++i) {
    container.push_back(i);
  }

  for (value_type i = 0; i < n_objects; ++i) {
    CHECK(container.at(i) == i);
  }
}

TEMPLATE_TEST_CASE("resource through allocator, std::list",
                   "[vanna][monotonic][resource][allocator][std::vector][stl]",
                   vanna::monotonic) {
  using value_type = std::uint32_t;
  using alloc_type = vanna::allocator<value_type>;
  using container_type = std::list<value_type, alloc_type>;
  using resource_type = TestType;

  auto constexpr n_objects = 1000;

  resource_type resource{};
  container_type container(&resource);

  for (value_type i = 0; i < n_objects; ++i) {
    container.push_back(i);
  }

  value_type i = 0;
  for (auto const& it : container) {
    CHECK(it == i++);
  }
}

TEMPLATE_TEST_CASE("resource throuth allocator, std::set",
                   "[vanna][monotonic][resource][allocator][std::vector][stl]",
                   vanna::monotonic) {
  using value_type = std::uint32_t;
  using alloc_type = vanna::allocator<value_type>;
  using container_type =
      std::set<value_type, std::less<value_type>, alloc_type>;
  using resource_type = TestType;

  auto constexpr n_objects = 1000;

  resource_type resource{};
  container_type container(&resource);

  for (value_type i = 0; i < n_objects; ++i) {
    container.insert(i);
  }

  value_type i = 0;
  for (auto const& it : container) {
    CHECK(it == i++);
  }
}

TEMPLATE_TEST_CASE("resource throuth allocator, std::map",
                   "[vanna][monotonic][resource][allocator][std::vector][stl]",
                   vanna::monotonic) {
  using value_type = std::uint32_t;
  using pair_type = std::pair<value_type const, value_type>;
  using alloc_type = vanna::allocator<pair_type>;
  using container_type =
      std::map<value_type, value_type, std::less<value_type>, alloc_type>;
  using resource_type = TestType;

  auto constexpr n_objects = 1000;

  resource_type resource{};
  container_type container(&resource);

  for (value_type i = 0; i < n_objects; ++i) {
    container[i] = i;
  }

  value_type i = 0;
  for (auto const& it : container) {
    CHECK(it.first == i);
    CHECK(it.second == i++);
  }
}
