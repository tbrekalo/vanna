find_package(benchmark REQUIRED)

set(${PROJECT_NAME}_benchmark_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/resource_benchmark.cxx
)

add_executable(${PROJECT_NAME}_benchmark ${${PROJECT_NAME}_benchmark_SOURCES})
target_link_libraries(${PROJECT_NAME}_benchmark ${PROJECT_NAME} benchmark::benchmark)