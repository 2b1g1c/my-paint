cmake_minimum_required(VERSION 3.27)
project(my-paint)

option(SANITIZE "Option referring to sanitizers (cppcheck, iwyu, additional warnings)" OFF)
option(BINARY_DEPS "Option referring to dependency installation (OFF - compile from source, ON - download binaries)" ON)
option(GENERATE_DEPENDENCY_GRAPH "Option referring to dependency graph generation in png format" OFF)
option(FORMAT_SOURCE "Option referring to formatting before compiling" OFF)

set(USE_CCACHE YES)

include(cmake/deps.cmake)

# add executable
add_executable(${CMAKE_PROJECT_NAME} "")
add_subdirectory(src)

# dependencies
target_link_libraries(
  ${CMAKE_PROJECT_NAME} PRIVATE
  ${DEPS_LIBRARIES}
)

target_include_directories(
  ${CMAKE_PROJECT_NAME} PUBLIC
  ${DEPS_INCLUDE_DIRS}
)

target_compile_definitions(
  ${CMAKE_PROJECT_NAME} PRIVATE
  ${DEPS_DEFINITIONS}
)

# source
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src
)
target_precompile_headers(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/pch.hpp
)

# copy assets
set(ASSET_DIR bin)
add_custom_target(copy-assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/${ASSET_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${ASSET_DIR}
)
add_dependencies(${CMAKE_PROJECT_NAME} copy-assets)

GroupSourcesByFolder(${CMAKE_PROJECT_NAME}) # better IDE integration
