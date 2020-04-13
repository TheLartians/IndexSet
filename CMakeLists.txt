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

FILE(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
FILE(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Add dependencies via CPM (if required) ----

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME BitLens
  GITHUB_REPOSITORY TheLartians/BitLens
  VERSION 2.1
)

CPMAddPackage(
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
    $<INSTALL_INTERFACE:include>
)

# ---- Create an installable target ----
# this allows users install and find the library via `find_package(IndexSet)`.

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib COMPONENT Runtime
  ARCHIVE DESTINATION lib COMPONENT Development
  RUNTIME DESTINATION bin COMPONENT Runtime
  PUBLIC_HEADER DESTINATION include COMPONENT Development
  BUNDLE DESTINATION bin COMPONENT Runtime
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
  EXPORT ${PROJECT_NAME}Targets 
  DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
  FILES 
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  DESTINATION 
    lib/cmake/${PROJECT_NAME}
)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION include
)
