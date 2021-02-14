#include "vanna/allocator.hpp"
#include "vanna/new_delete.hpp"

#include "catch2/catch.hpp"

TEST_CASE("new_delete resource", "[vanna][resource][new_delete]") {
  using value_type = std::uint32_t;
  using pointer = value_type*;

  auto& resource = *vanna::get_new_delete();

  auto raw_mem = reinterpret_cast<pointer>(
      resource.allocate(sizeof(value_type), alignof(value_type)));
  new (raw_mem) value_type(42);

  REQUIRE(*raw_mem == 42);

  resource.deallocate(reinterpret_cast<vanna::resource::pointer>(raw_mem),
                      sizeof(value_type), alignof(value_type));
}

TEST_CASE("new_delete resource through allocator", "[vanna][resource][new_delete][allocator]") {
  using value_type = std::uint32_t;
  using alloc_type =  vanna::allocator<value_type>;
  using container_type = std::vector<value_type, alloc_type>;

  auto constexpr n_objects = 100;

  container_type container(vanna::get_new_delete());
  container.reserve(n_objects);

  CHECK(container.capacity() == n_objects);

  for (value_type i = 0; i < n_objects; ++i) {
    container.push_back(i);
  }

  for (value_type i = 0; i < n_objects; ++i) {
    CHECK(container.at(i) == i);
  }
}