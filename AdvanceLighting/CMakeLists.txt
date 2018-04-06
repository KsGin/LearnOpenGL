cmake_minimum_required(VERSION 3.10)
project(AdvanceLighting)

set(CMAKE_CXX_STANDARD 11)

AUX_SOURCE_DIRECTORY(./Sources SRC_SOURCES)
AUX_SOURCE_DIRECTORY(./Headers HRC_SOURCES)

add_executable(
        AdvanceLighting main.cpp
        ./Headers/Model.h
        ./Headers/Shader.h
        ./Sources/Model.cpp
        ./Sources/Shader.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL")

target_link_libraries(AdvanceLighting /usr/local/lib/libglfw.dylib)

target_link_libraries(AdvanceLighting /usr/local/lib/libGLEW.dylib)