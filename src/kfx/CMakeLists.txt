

# add_executable(
#   kfx

#   Components.cpp
#   Engine.cpp
#   GameObject.cpp
#   GameObjectFactory.cpp
#   Handle.cpp
#   HandleManager.cpp
#   main.cpp 
#   Message.cpp 
# 	MessageBox.cpp 
	
#   input/InputSystem.cpp

#   resources/FileUtil.cpp
#   resources/MeshManager.cpp
#   resources/MeshUtil.cpp
#   resources/ShaderManager.cpp
#   resources/ShaderUtil.cpp

#   system/GraphicsSystem3D.cpp
#   system/System.cpp
# )

add_library(
  kfx
  
  STATIC
  
  Assert.cpp
  Components.cpp
  Clock.cpp
  Engine.cpp
  GameObjectFactory.cpp
  Handle.cpp
  HandleManager.cpp
  MessageBox.cpp 
  Window.cpp
  KeyboardInputPeripheral.cpp
  MouseInputPeripheral.cpp
  
  resources/FileUtil.cpp
  resources/MeshManager.cpp
  resources/MeshUtil.cpp
  resources/ShaderManager.cpp
  resources/ShaderUtil.cpp
  resources/TextureManager.cpp
  resources/TextureUtil.cpp
  resources/MaterialParser.cpp
  resources/MaterialManager.cpp
  
  system/FpsInputSystem.cpp
  system/GraphicsSystem3D.cpp
  system/MeshSystem.cpp
  system/TransformSystem.cpp
  system/System.cpp
  
  graphics/Renderer3D.cpp
  graphics/Mesh.cpp
  graphics/Shader.cpp
  graphics/Texture.cpp
  graphics/Material.cpp
)


target_include_directories(kfx 
  PRIVATE 
    "${kfx_SOURCE_DIR}/src"
    "${kfx_SOURCE_DIR}/include"
    "${GLFW_SOURCE_DIR}/include"
    "${glew_SOURCE_DIR}/../../include"  
)

# target_compile_definitions(kfx 
#   PUBLIC GLFW_DLL 
#   PRIVATE GLEW_STATIC
# )

target_compile_features(kfx
  PUBLIC 
    cxx_std_17
    # cxx_final
    # cxx_lambdas
    # cxx_nullptr
    # cxx_override
    # cxx_range_for
)

target_link_libraries(kfx stdc++fs glfw glew lodepng)

# So that VS recognizes our resource files
set_target_properties(kfx PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")

set_target_properties(kfx PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(kfx PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(kfx PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

set_target_properties(glfw PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(glfw PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(glfw PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

set_target_properties(glew PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(glew PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(glew PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

set_target_properties(lodepng PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(lodepng PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(lodepng PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

# Do I need this?
# install(TARGETS kfx EXPORT kfxTargets
# 	LIBRARY DESTINATION lib
# 	ARCHIVE DESTINATION lib
# 	RUNTIME DESTINATION bin
# 	INCLUDES DESTINATION include
# 	)