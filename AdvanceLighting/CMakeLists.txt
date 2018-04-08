cmake_minimum_required(VERSION 3.10)
project(AdvanceLighting)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        AdvanceLighting main.cpp
        Headers/Shader.hpp
        Headers/Camera.hpp
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(AdvanceLighting /usr/local/lib/libglfw.dylib)

target_link_libraries(AdvanceLighting /usr/local/lib/libGLEW.dylib)