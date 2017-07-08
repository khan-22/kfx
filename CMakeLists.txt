CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(kfx)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

message("Current Platform: ${CMAKE_SYSTEM_NAME}")

## To enable me building glfw from source
#include(ExternalProject)
#ExternalProject_Add(
#    project_glfw
#    URL "https://github.com/glfw/glfw/archive/3.2.1.tar.gz"
#    URL_HASH SHA1=bee9cd9a8b4925184070ade5bc287c5635830eb0
#    CMAKE_ARGS "-DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}"
#    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/glfw-3.2.1
#)
#
#ExternalProject_Get_Property(project_glfw install_dir)
#add_library(glfw SHARED IMPORTED)
#set_property(TARGET glfw PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libglfw.so)
#
#add_dependencies(glfw project_glfw)


include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

#add_subdirectory(${PROJECT_SOURCE_DIR}/glfw-master)
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
