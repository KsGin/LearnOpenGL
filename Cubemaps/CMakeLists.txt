cmake_minimum_required(VERSION 3.9)
project(Cubemaps)

set(CMAKE_CXX_STANDARD 11)

add_executable(Cubemaps main.cpp shader.hpp stb_image.h camera.hpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(Cubemaps "/usr/local/lib/libglfw.dylib")

target_link_libraries(Cubemaps "/usr/local/lib/libGLEW.dylib")

target_link_libraries(Cubemaps "/usr/local/lib/libassimp.dylib")