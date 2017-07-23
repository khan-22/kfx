#file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(SOURCES 
	main.cpp 
	
  Message.cpp 
	MessageBox.cpp 

  GameObject.cpp
  GameObjectFactory.cpp
  Components.cpp

  Handle.cpp
  HandleManager.cpp

  Engine.cpp

  input/InputSystem.cpp
  
  system/System.cpp
  system/GraphicsSystem3D.cpp
  
  resources/MeshManager.cpp
  resources/ShaderManager.cpp
  resources/FileUtil.cpp
  resources/ShaderUtil.cpp
  resources/MeshUtil.cpp)

FOREACH(SRC ${SOURCES})
  LIST(APPEND SRC2 "${PROJECT_SOURCE_DIR}/src/${SRC}")
ENDFOREACH()

#message("Source files: ${SOURCES}")

add_executable(
  kfx
  ${SRC2}
)
target_include_directories(kfx PRIVATE "${PROJECT_SOURCE_DIR}/include")
link_directories("${PROJECT_SOURCE_DIR}/lib")

add_definitions(-DGLFW_DLL -DGLEW_STATIC)

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

# So that VS recognizes our resource files
set_target_properties(kfx PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
