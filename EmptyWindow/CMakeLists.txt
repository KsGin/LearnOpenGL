cmake_minimum_required(VERSION 3.8)
project(EmptyWindow)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")
set(SOURCE_FILES main.cpp)
add_executable(EmptyWindow ${SOURCE_FILES})

target_link_libraries(EmptyWindow "/usr/local/lib/libglfw.dylib")

target_link_libraries(EmptyWindow "/usr/local/lib/libGLEW.dylib")