cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ---- Project ----

project(IndexSet 
  VERSION 1.0
  LANGUAGES CXX
)

# ---- Include guards ----

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# ---- Add source files ----

FILE(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
FILE(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Add dependencies via CPM (if required) ----

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.0
)

CPMFindPackage(
  NAME BitLens
  GITHUB_REPOSITORY TheLartians/BitLens
  VERSION 2.1
)

CPMFindPackage(
  NAME EasyIterator
  VERSION 1.3
  GITHUB_REPOSITORY TheLartians/EasyIterator
)

# ---- Create library ----

add_library(IndexSet ${headers} ${sources})

set_target_properties(IndexSet PROPERTIES CXX_STANDARD 17)

# Link dependencies
target_link_libraries(IndexSet PUBLIC BitLens EasyIterator)

# Node: change PUBLIC to INTERFACE for single header libraries  
target_include_directories(IndexSet
  PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
)
