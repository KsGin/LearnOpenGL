cmake_minimum_required(VERSION 3.8)
project(HelloTriangle)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(HelloTriangle ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(HelloTriangle "/usr/local/lib/libglfw.dylib")

target_link_libraries(HelloTriangle "/usr/local/lib/libGLEW.dylib")