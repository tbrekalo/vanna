cmake_minimum_required(VERSION 3.19)
project(vanna VERSION 0.0.1 LANGUAGES CXX)


# build specification
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)


# c++ config
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED)
list(APPEND CMAKE_CXX_FALGS "-Wall -Wextra -pedantic")


# target
set(${PROJECT_NAME}_PMR_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vanna/pmr/memory_resource.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vanna/pmr/monotonic_buffer.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vanna/pmr/new_delete_resource.cxx
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_PMR_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)