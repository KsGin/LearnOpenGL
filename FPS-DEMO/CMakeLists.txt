cmake_minimum_required(VERSION 3.9)
project(FPS_DEMO)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp shader.hpp Mesh.cpp Mesh.h Model.h stb_image.h Model.cpp)

add_executable(FPS_DEMO ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(FPS_DEMO "/usr/local/lib/libglfw.dylib")

target_link_libraries(FPS_DEMO "/usr/local/lib/libGLEW.dylib")

target_link_libraries(FPS_DEMO "/usr/local/lib/libassimp.dylib")