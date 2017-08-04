add_executable(
  example_basic

  basic-main.cpp
)

target_include_directories( example_basic
  PRIVATE  
    ${kfx_SOURCE_DIR}/include
)

target_link_libraries(
  example_basic kfx
)

