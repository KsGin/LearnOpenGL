# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/KsGin/Documents/OpenGL/Transformations

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/KsGin/Documents/OpenGL/Transformations/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Transformations.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Transformations.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Transformations.dir/flags.make

CMakeFiles/Transformations.dir/main.cpp.o: CMakeFiles/Transformations.dir/flags.make
CMakeFiles/Transformations.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/KsGin/Documents/OpenGL/Transformations/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Transformations.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Transformations.dir/main.cpp.o -c /Users/KsGin/Documents/OpenGL/Transformations/main.cpp

CMakeFiles/Transformations.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Transformations.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/KsGin/Documents/OpenGL/Transformations/main.cpp > CMakeFiles/Transformations.dir/main.cpp.i

CMakeFiles/Transformations.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Transformations.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/KsGin/Documents/OpenGL/Transformations/main.cpp -o CMakeFiles/Transformations.dir/main.cpp.s

CMakeFiles/Transformations.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Transformations.dir/main.cpp.o.requires

CMakeFiles/Transformations.dir/main.cpp.o.provides: CMakeFiles/Transformations.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Transformations.dir/build.make CMakeFiles/Transformations.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Transformations.dir/main.cpp.o.provides

CMakeFiles/Transformations.dir/main.cpp.o.provides.build: CMakeFiles/Transformations.dir/main.cpp.o


CMakeFiles/Transformations.dir/shader.cpp.o: CMakeFiles/Transformations.dir/flags.make
CMakeFiles/Transformations.dir/shader.cpp.o: ../shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/KsGin/Documents/OpenGL/Transformations/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Transformations.dir/shader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Transformations.dir/shader.cpp.o -c /Users/KsGin/Documents/OpenGL/Transformations/shader.cpp

CMakeFiles/Transformations.dir/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Transformations.dir/shader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/KsGin/Documents/OpenGL/Transformations/shader.cpp > CMakeFiles/Transformations.dir/shader.cpp.i

CMakeFiles/Transformations.dir/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Transformations.dir/shader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/KsGin/Documents/OpenGL/Transformations/shader.cpp -o CMakeFiles/Transformations.dir/shader.cpp.s

CMakeFiles/Transformations.dir/shader.cpp.o.requires:

.PHONY : CMakeFiles/Transformations.dir/shader.cpp.o.requires

CMakeFiles/Transformations.dir/shader.cpp.o.provides: CMakeFiles/Transformations.dir/shader.cpp.o.requires
	$(MAKE) -f CMakeFiles/Transformations.dir/build.make CMakeFiles/Transformations.dir/shader.cpp.o.provides.build
.PHONY : CMakeFiles/Transformations.dir/shader.cpp.o.provides

CMakeFiles/Transformations.dir/shader.cpp.o.provides.build: CMakeFiles/Transformations.dir/shader.cpp.o


CMakeFiles/Transformations.dir/texture.cpp.o: CMakeFiles/Transformations.dir/flags.make
CMakeFiles/Transformations.dir/texture.cpp.o: ../texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/KsGin/Documents/OpenGL/Transformations/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Transformations.dir/texture.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Transformations.dir/texture.cpp.o -c /Users/KsGin/Documents/OpenGL/Transformations/texture.cpp

CMakeFiles/Transformations.dir/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Transformations.dir/texture.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/KsGin/Documents/OpenGL/Transformations/texture.cpp > CMakeFiles/Transformations.dir/texture.cpp.i

CMakeFiles/Transformations.dir/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Transformations.dir/texture.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/KsGin/Documents/OpenGL/Transformations/texture.cpp -o CMakeFiles/Transformations.dir/texture.cpp.s

CMakeFiles/Transformations.dir/texture.cpp.o.requires:

.PHONY : CMakeFiles/Transformations.dir/texture.cpp.o.requires

CMakeFiles/Transformations.dir/texture.cpp.o.provides: CMakeFiles/Transformations.dir/texture.cpp.o.requires
	$(MAKE) -f CMakeFiles/Transformations.dir/build.make CMakeFiles/Transformations.dir/texture.cpp.o.provides.build
.PHONY : CMakeFiles/Transformations.dir/texture.cpp.o.provides

CMakeFiles/Transformations.dir/texture.cpp.o.provides.build: CMakeFiles/Transformations.dir/texture.cpp.o


# Object files for target Transformations
Transformations_OBJECTS = \
"CMakeFiles/Transformations.dir/main.cpp.o" \
"CMakeFiles/Transformations.dir/shader.cpp.o" \
"CMakeFiles/Transformations.dir/texture.cpp.o"

# External object files for target Transformations
Transformations_EXTERNAL_OBJECTS =

Transformations: CMakeFiles/Transformations.dir/main.cpp.o
Transformations: CMakeFiles/Transformations.dir/shader.cpp.o
Transformations: CMakeFiles/Transformations.dir/texture.cpp.o
Transformations: CMakeFiles/Transformations.dir/build.make
Transformations: /usr/local/lib/libglfw.dylib
Transformations: /usr/local/lib/libGLEW.dylib
Transformations: CMakeFiles/Transformations.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/KsGin/Documents/OpenGL/Transformations/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Transformations"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Transformations.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Transformations.dir/build: Transformations

.PHONY : CMakeFiles/Transformations.dir/build

CMakeFiles/Transformations.dir/requires: CMakeFiles/Transformations.dir/main.cpp.o.requires
CMakeFiles/Transformations.dir/requires: CMakeFiles/Transformations.dir/shader.cpp.o.requires
CMakeFiles/Transformations.dir/requires: CMakeFiles/Transformations.dir/texture.cpp.o.requires

.PHONY : CMakeFiles/Transformations.dir/requires

CMakeFiles/Transformations.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Transformations.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Transformations.dir/clean

CMakeFiles/Transformations.dir/depend:
	cd /Users/KsGin/Documents/OpenGL/Transformations/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/KsGin/Documents/OpenGL/Transformations /Users/KsGin/Documents/OpenGL/Transformations /Users/KsGin/Documents/OpenGL/Transformations/cmake-build-debug /Users/KsGin/Documents/OpenGL/Transformations/cmake-build-debug /Users/KsGin/Documents/OpenGL/Transformations/cmake-build-debug/CMakeFiles/Transformations.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Transformations.dir/depend

