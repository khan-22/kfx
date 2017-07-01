file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#message("Source files: ${SOURCES}")

add_executable(
  kfx
  ${SOURCES}
)
target_include_directories(kfx PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(
  kfx
  ${PROJECT_SOURCE_DIR}/lib/libglfw.so
)
