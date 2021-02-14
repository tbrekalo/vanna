find_package(Catch2 REQUIRED)

set(${PROJECT_NAME}_test_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/new_delete_test.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/stl_containers.cxx
)

add_executable(${PROJECT_NAME}_test ${${PROJECT_NAME}_test_SOURCES})

target_include_directories(${PROJECT_NAME}_test PRIVATE ${CATCH_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME} Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}_test)