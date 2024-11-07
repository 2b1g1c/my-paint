file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

if (${CMAKE_HOST_SYSTEM} MATCHES "Linux")
  CPMAddPackage(
    NAME nlohmann_json
    VERSION 3.7.3
    # the git repo is incredibly large, so we download the archived include directory
    URL https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip
    URL_HASH SHA256=87b5884741427220d3a33df1363ae0e8b898099fbc59f1c451113f6732891014
  )

  if (nlohmann_json_ADDED)
    add_library(nlohmann_json INTERFACE IMPORTED)
    target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_SOURCE_DIR}/include)
  endif()
endif()

CPMAddPackage(
  NAME imgui_bundle
  GIT_TAG main
  GITHUB_REPOSITORY pthom/imgui_bundle
)

# set important variables
set(DEPS_LIBRARIES
  nlohmann_json
)
if (WIN32)
  set(DEPS_LIBRARIES ${DEPS_LIBRARIES} opengl32)
else()
  set(DEPS_LIBRARIES ${DEPS_LIBRARIES} GL)
endif()

set(DEPS_INCLUDE_DIRS
)

set(DEPS_DEFINITIONS
)

# install CMake scripts
include(${CMAKE_SOURCE_DIR}/cmake/scripts.cmake)
