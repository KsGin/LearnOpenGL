cmake_minimum_required(VERSION 3.9)
project(3D_Model)

set(CMAKE_CXX_STANDARD 11)


add_executable(3D_Model main.cpp Mesh.h shader.hpp Mesh.cpp Model.cpp Model.h stb_image.h)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(3D_Model "/usr/local/lib/libglfw.dylib")
target_link_libraries(3D_Model "/usr/local/lib/libGLEW.dylib")
target_link_libraries(3D_Model "/usr/local/lib/libassimp.dylib")