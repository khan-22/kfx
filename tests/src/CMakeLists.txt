add_executable(kfx_tests
  test-main.cpp  

  # Meta test
  test-test.cpp

  test-file-utilities.cpp
  test-shader-utilities.cpp

  test-mesh-manager.cpp
  test-handle-manager.cpp
  test-game-object-factory.cpp
  test-shader-manager.cpp
  test-message-box.cpp
  test-handled-resource.cpp
  test-window.cpp
)

target_include_directories(kfx_tests
    PRIVATE 
      ${kfx_SOURCE_DIR}/include/
      ${kfx_SOURCE_DIR}/tests/include/
)

target_link_libraries(kfx_tests kfx)


# set_target_properties(kfx_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
# set_target_properties(kfx_tests PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
# set_target_properties(kfx_tests PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")