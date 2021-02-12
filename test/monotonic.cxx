#include <vector>
#include <list>
#include <set>

#include "catch2/catch.hpp"

#include "vanna/monotonic.hpp"
#include "vanna/allocator.hpp"

TEST_CASE("monotonic resource through allocator",
          "[vanna][monotonic][resource][allocator]") {
  auto resource = vanna::monotonic();
}