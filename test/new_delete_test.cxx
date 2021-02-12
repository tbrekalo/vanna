#include "vanna/new_delete.hpp"

#include "catch2/catch.hpp"

TEST_CASE("new_delete", "[vanna][resource][new_delete]") {
  using value_type = std::uint32_t;
  using pointer = value_type*;
  vanna::new_delete resource{};

  auto raw_mem = reinterpret_cast<pointer>(
      resource.allocate(sizeof(value_type), alignof(value_type)));
  new (raw_mem) value_type(42);

  REQUIRE(*raw_mem == 42);

  resource.deallocate(reinterpret_cast<vanna::new_delete::pointer>(raw_mem),
                      sizeof(value_type), alignof(value_type));
}