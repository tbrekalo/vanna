find_package(Catch2 REQUIRED)

add_executable(
  vanna_test
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/new_delete_test.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/monotonic_test.cxx)


target_include_directories(vanna_test PRIVATE ${CATCH_INCLUDE_DIRS})
target_link_libraries(vanna_test ${PROJECT_NAME} Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(vanna_test)