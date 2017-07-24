CMAKE_MINIMUM_REQUIRED(VERSION 3.9.0)

set(CMAKE_BUILD_TYPE Debug)

project(kfx VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${kfx_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${kfx_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${kfx_SOURCE_DIR}/lib)

message("Current Platform: ${CMAKE_SYSTEM_NAME}")

# Glfw dependency
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)

# Glew dependency
add_subdirectory(deps/glew-2.0.0/build/cmake)

# The main source code of the library
add_subdirectory(src/kfx)

# Adds the unit tests
add_subdirectory(tests/src)
enable_testing()
add_test(NAME kfx_tests COMMAND kfx_tests)
