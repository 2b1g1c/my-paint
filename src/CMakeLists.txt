file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR} *.hpp)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${SOURCES} ${HEADERS})

add_library(GLAD glad/glad.c)
target_include_directories(GLAD PRIVATE . glad)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE GLAD)
