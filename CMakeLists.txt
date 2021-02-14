cmake_minimum_required(VERSION 3.19)
project(vanna VERSION 0.0.1 LANGUAGES C CXX)


# build specification
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# c config
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

# c++ config

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# target
set(${PROJECT_NAME}_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vanna/default.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vanna/resource.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vanna/monotonic.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vanna/new_delete.cxx
)


add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

# benchmarks
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/benchmark)