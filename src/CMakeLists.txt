

add_executable(
  kfx

  Components.cpp
  Engine.cpp
  GameObject.cpp
  GameObjectFactory.cpp
  Handle.cpp
  HandleManager.cpp
  main.cpp 
  Message.cpp 
	MessageBox.cpp 
	
  input/InputSystem.cpp

  resources/FileUtil.cpp
  resources/MeshManager.cpp
  resources/MeshUtil.cpp
  resources/ShaderManager.cpp
  resources/ShaderUtil.cpp

  system/GraphicsSystem3D.cpp
  system/System.cpp
)
target_include_directories(kfx PRIVATE "${PROJECT_SOURCE_DIR}/include")

# target_compile_definitions(kfx 
#   PUBLIC GLFW_DLL 
#   PRIVATE GLEW_STATIC
# )

target_compile_features(kfx
  PUBLIC 
    cxx_std_14
    # cxx_final
    # cxx_lambdas
    # cxx_nullptr
    # cxx_override
    # cxx_range_for
)

target_link_libraries(kfx glfw glew)

# So that VS recognizes our resource files
set_target_properties(kfx PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")

set_target_properties(kfx PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(kfx PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(kfx PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

# Do I need this?
# install(TARGETS kfx EXPORT kfxTargets
# 	LIBRARY DESTINATION lib
# 	ARCHIVE DESTINATION lib
# 	RUNTIME DESTINATION bin
# 	INCLUDES DESTINATION include
# 	)