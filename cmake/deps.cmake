file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage(
  NAME imgui_bundle
  GIT_TAG main
  GITHUB_REPOSITORY pthom/imgui_bundle
  OPTIONS
    "HELLOIMGUI_DOWNLOAD_FREETYPE_IF_NEEDED ON"
)

if (NOT TARGET nlohmann_json)
  CPMAddPackage(
    NAME nlohmann_json
    GIT_TAG develop
    GITHUB_REPOSITORY nlohmann/json
  )
endif()

file(
	DOWNLOAD
	https://raw.githubusercontent.com/yhirose/cpp-httplib/refs/heads/master/httplib.h
	${CMAKE_CURRENT_BINARY_DIR}/_deps/cpp-httplib-src/httplib/httplib.h
	EXPECTED_HASH SHA256=27e32e1f8950b5e5760ee7c4f7d480d2950812639d8f892e3ff6f590ffb1bf61
)
add_library(httplib INTERFACE)
target_include_directories(httplib INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/_deps/cpp-httplib-src)

# set important variables
set(DEPS_LIBRARIES
  nlohmann_json
  httplib
)

set(DEPS_INCLUDE_DIRS
)

set(DEPS_DEFINITIONS
)

# install CMake scripts
include(${CMAKE_SOURCE_DIR}/cmake/scripts.cmake)
