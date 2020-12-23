#include <functional>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <new>

#include "catch2/catch.hpp"
#include "vanna/monotonic.hpp"

TEST_CASE("vanna::monotonic std::list", "[vanna][monotonic][std::list]") {
  using value_type = std::uint32_t;

  auto constexpr n = 1000U;
  auto list = std::list<value_type, vanna::monotonic<value_type, n>>();

  for (value_type i = 0; i < n + 1; ++i) {
    list.push_back(i);
  }

  value_type i = 0U;
  for (auto it : list) {
    REQUIRE(it == i++);
  }
}

TEST_CASE("vanna::monotonic std::vector", "[vanna][monotonic][std::vector]") {
  using value_type = std::uint32_t;

  auto constexpr n = 1000UL;
  auto constexpr capacity = 1024;
  auto vector =
      std::vector<value_type, vanna::monotonic<value_type, capacity>>();

  for (value_type i = 0; i < n; ++i) {
    vector.push_back(i);
  }

  value_type i = 0;
  for (auto it : vector) {
    REQUIRE(it == i++);
  }
}

TEST_CASE("vanna::monotonic std::set", "[vanna][monotonic][std::set]") {
  using value_type = std::uint32_t;

  auto constexpr n = 1000UL;
  auto set = std::set<value_type, std::less<value_type>,
                      vanna::monotonic<value_type, n>>();

  for (value_type i = 0; i < n + 1; ++i) {
    set.insert(i);
  }

  value_type i = 0U;
  for (auto it : set) {
    REQUIRE(it == i++);
  }
}

TEST_CASE("vanna::monotonic std::map", "[vanna][monotonic][std::map]") {
  using value_type = std::uint32_t;

  auto constexpr n = 1000UL;
  auto map =
      std::map<value_type, value_type, std::less<value_type>,
               vanna::monotonic<std::pair<value_type const, value_type>, n>>();

  for (value_type i = 0; i < n + 1; ++i) {
    map.emplace(i, n - i);
  }

  value_type i = 0;
  for (auto const& it : map) {
    CHECK(it.first == i);
    REQUIRE(it.second == n - i);
  
    ++i;
  }
}
