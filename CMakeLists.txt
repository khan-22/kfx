CMAKE_MINIMUM_REQUIRED(VERSION 3.9.0)

set(CMAKE_BUILD_TYPE Debug)

project(kfx)

message("Current Platform: ${CMAKE_SYSTEM_NAME}")

message("${CMAKE_CXX_KNOWN_FEATURES}")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)

add_subdirectory(deps/glew-2.0.0/build/cmake)

add_subdirectory(src)
