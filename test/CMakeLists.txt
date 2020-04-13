cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(IndexSetTests
  LANGUAGES CXX
)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY onqtam/doctest
  VERSION 2.3.2
  GIT_TAG 2.3.2
)

if (TEST_INSTALLED_VERSION)
  find_package(IndexSet)
else()
  CPMAddPackage(
    NAME IndexSet
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
  )
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.0
)

# ---- Create binary ----

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(IndexSetTests ${sources})
target_link_libraries(IndexSetTests doctest IndexSet)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set_target_properties(IndexSetTests PROPERTIES CXX_STANDARD 17 COMPILE_FLAGS "-Wall -pedantic -Wextra -Werror")
else()
  set_target_properties(IndexSetTests PROPERTIES CXX_STANDARD 17)
endif()

# ---- Add IndexSetTests ----

ENABLE_TESTING() 
ADD_TEST(IndexSetTests IndexSetTests)

# ---- code coverage ----

if (${ENABLE_TEST_COVERAGE})
  set_target_properties(IndexSet PROPERTIES CXX_STANDARD 17 COMPILE_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage --coverage")
  target_link_options(IndexSet PUBLIC "--coverage")
endif()
