file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#message("Source files: ${SOURCES}")

add_executable(
  kfx
  ${SOURCES}
)
target_include_directories(kfx PRIVATE "${PROJECT_SOURCE_DIR}/include")
link_directories("${PROJECT_SOURCE_DIR}/lib")

add_definitions(-DGLFW_DLL)

if(UNIX)
  target_link_libraries(
    kfx
    #${PROJECT_SOURCE_DIR}/lib/libglfw.so
    libglfw.so libGLEW.a libGL.so
  )
elseif(WIN32)
  target_link_libraries(
    kfx
    glfw3dll.lib glew32s.lib opengl32.lib
  )
endif()
