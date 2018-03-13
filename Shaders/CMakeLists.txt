cmake_minimum_required(VERSION 3.9)
project(Shaders)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")
set(CMAKE_CXX_STANDARD 11)

add_executable(Shaders main.cpp)

target_link_libraries(Shaders "/usr/local/lib/libglfw.dylib")

target_link_libraries(Shaders "/usr/local/lib/libGLEW.dylib")