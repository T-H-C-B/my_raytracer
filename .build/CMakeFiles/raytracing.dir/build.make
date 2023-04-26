# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Bartosz/delivery/RayTracer/my_raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Bartosz/delivery/RayTracer/my_raytracer/.build

# Include any dependencies generated for this target.
include CMakeFiles/raytracing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raytracing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raytracing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raytracing.dir/flags.make

CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.o: CMakeFiles/raytracing.dir/flags.make
CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.o: ../sources/Core/Loader/DynamicLibrary.cpp
CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.o: CMakeFiles/raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Bartosz/delivery/RayTracer/my_raytracer/.build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.o -MF CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.o.d -o CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.o -c /home/Bartosz/delivery/RayTracer/my_raytracer/sources/Core/Loader/DynamicLibrary.cpp

CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Bartosz/delivery/RayTracer/my_raytracer/sources/Core/Loader/DynamicLibrary.cpp > CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.i

CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Bartosz/delivery/RayTracer/my_raytracer/sources/Core/Loader/DynamicLibrary.cpp -o CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.s

CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.o: CMakeFiles/raytracing.dir/flags.make
CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.o: ../sources/Core/Loader/SceneLoader.cpp
CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.o: CMakeFiles/raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Bartosz/delivery/RayTracer/my_raytracer/.build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.o -MF CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.o.d -o CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.o -c /home/Bartosz/delivery/RayTracer/my_raytracer/sources/Core/Loader/SceneLoader.cpp

CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Bartosz/delivery/RayTracer/my_raytracer/sources/Core/Loader/SceneLoader.cpp > CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.i

CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Bartosz/delivery/RayTracer/my_raytracer/sources/Core/Loader/SceneLoader.cpp -o CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.s

# Object files for target raytracing
raytracing_OBJECTS = \
"CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.o" \
"CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.o"

# External object files for target raytracing
raytracing_EXTERNAL_OBJECTS =

../raytracing: CMakeFiles/raytracing.dir/sources/Core/Loader/DynamicLibrary.cpp.o
../raytracing: CMakeFiles/raytracing.dir/sources/Core/Loader/SceneLoader.cpp.o
../raytracing: CMakeFiles/raytracing.dir/build.make
../raytracing: ../libraytracer_lib.a
../raytracing: CMakeFiles/raytracing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Bartosz/delivery/RayTracer/my_raytracer/.build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../raytracing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytracing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raytracing.dir/build: ../raytracing
.PHONY : CMakeFiles/raytracing.dir/build

CMakeFiles/raytracing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raytracing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raytracing.dir/clean

CMakeFiles/raytracing.dir/depend:
	cd /home/Bartosz/delivery/RayTracer/my_raytracer/.build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Bartosz/delivery/RayTracer/my_raytracer /home/Bartosz/delivery/RayTracer/my_raytracer /home/Bartosz/delivery/RayTracer/my_raytracer/.build /home/Bartosz/delivery/RayTracer/my_raytracer/.build /home/Bartosz/delivery/RayTracer/my_raytracer/.build/CMakeFiles/raytracing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raytracing.dir/depend

