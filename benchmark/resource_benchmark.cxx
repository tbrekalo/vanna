#include <cstdint>
#include <vector>
#include <list>

#include "benchmark/benchmark.h"
#include "vanna/monotonic.hpp"
#include "vanna/allocator.hpp"

namespace vanna {
namespace benchmark {
namespace simple_types {

using value_type = std::uint32_t;
using size_type = std::size_t;

using alloc_type = vanna::allocator<value_type>;

using vector_type = std::vector<value_type, alloc_type>;
using list_type = std::list<value_type, alloc_type>;

size_type constexpr N_OBJECTS = 1e4;
value_type constexpr DUMMY = 0;

} // namespace simple_types
} // namespace benchmark
} // namespace vanna

static void BM_std_vector(benchmark::State& state) {
  using namespace vanna::benchmark::simple_types;
  for (auto _ : state) {
    std::vector<value_type> vec(N_OBJECTS, DUMMY);
  }
}

BENCHMARK(BM_std_vector);

static void BM_std_list(benchmark::State& state) {
  using namespace vanna::benchmark::simple_types;
  for (auto _ : state) {
    std::list<value_type> vec(N_OBJECTS, DUMMY);
  }
}

BENCHMARK(BM_std_list);

static void BM_monotonic_vector(benchmark::State& state) {
  using namespace vanna::benchmark::simple_types;
  for (auto _ : state) {
    vanna::monotonic resource((N_OBJECTS + 11) * sizeof(value_type));
    vector_type vec(N_OBJECTS, DUMMY, &resource);
  }
}

BENCHMARK(BM_monotonic_vector);


static void BM_monotonic_list(benchmark::State& state) {
  using namespace vanna::benchmark::simple_types;
  for (auto _ : state) {
    vanna::monotonic resource((N_OBJECTS) * 4 * sizeof(value_type));
    list_type vec(N_OBJECTS, DUMMY, &resource);
  }
}

BENCHMARK(BM_monotonic_list);

BENCHMARK_MAIN();