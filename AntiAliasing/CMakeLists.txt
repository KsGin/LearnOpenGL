cmake_minimum_required(VERSION 3.9)
project(AntiAliasing)

set(SOURCE_FILES main.cpp shader.cpp shader.h)
add_executable(AntiAliasing ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(AntiAliasing "/usr/local/lib/libglfw.dylib")

target_link_libraries(AntiAliasing "/usr/local/lib/libGLEW.dylib")