CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(kfx)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(${PROJECT_SOURCE_DIR}/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

#message("Binary Tree path: ${PROJECT_BINARY_DIR}")
#message("Project Source path: ${PROJECT_SOURCE_DIR}")

#file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

#message("Sources: ${SOURCES}")

#
#add_executable(
#  kfx
#  ${SOURCES}
#)
#target_link_libraries(
#  kfx
#  ${PROJECT_SOURCE_DIR}/lib/libglfw.so
#)


#add_subdirectory()
