CMAKE_MINIMUM_REQUIRED(VERSION 3.9.0)

#set(CMAKE_BUILD_TYPE Debug)

message("Current Build Type: ${CMAKE_BUILD_TYPE}")

project(kfx)
set(kfx_VERSION_MAJOR 0)
set(kfx_VERSION_MINOR 1)
set(kfx_VERSION_PATCH 0)
set(kfx_VERSION ${kfx_VERSION_MAJOR}.${kfx_VERSION_MINOR}.${kfx_VERSION_PATCH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

message("Runtime Output Directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("Archive Output Directory ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message("Library Output Directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")


message("Current Platform: ${CMAKE_SYSTEM_NAME}")



# Glfw dependency
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)

# Glew dependency
add_subdirectory(deps/glew-2.0.0/build/cmake)

# lodepng
add_subdirectory(deps/lodepng)

# The main source code of the library
add_subdirectory(src/kfx)

# Adds the unit tests
add_subdirectory(tests/src)
enable_testing()
add_test(NAME kfx_tests COMMAND kfx_tests)

# Adds the examples
add_subdirectory(examples)