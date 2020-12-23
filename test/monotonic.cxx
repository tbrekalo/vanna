#include <algorithm>
#include <iterator>
#include <cstdint>
#include <vector>
#include <list>

#include "catch2/catch.hpp"
#include "vanna/monotonic.hpp"

TEST_CASE("vanna::monotonic construction", "[vanna][monotonic]") {
  using value_type = std::uint32_t;

  auto constexpr n = 1000;
  auto constexpr chunk_size = n * sizeof(value_type);

  auto list = std::list<value_type, vanna::monotonic<value_type, chunk_size>>();
  
  std::generate_n(std::back_inserter(list), 2, [](){ return value_type(); });
}