# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /snap/clion/326/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/326/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bia/Documents/feup/DA/ProjectDA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/untitled.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/untitled.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled.dir/flags.make

CMakeFiles/untitled.dir/main.cpp.o: CMakeFiles/untitled.dir/flags.make
CMakeFiles/untitled.dir/main.cpp.o: /home/bia/Documents/feup/DA/ProjectDA/main.cpp
CMakeFiles/untitled.dir/main.cpp.o: CMakeFiles/untitled.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/untitled.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/untitled.dir/main.cpp.o -MF CMakeFiles/untitled.dir/main.cpp.o.d -o CMakeFiles/untitled.dir/main.cpp.o -c /home/bia/Documents/feup/DA/ProjectDA/main.cpp

CMakeFiles/untitled.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/untitled.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bia/Documents/feup/DA/ProjectDA/main.cpp > CMakeFiles/untitled.dir/main.cpp.i

CMakeFiles/untitled.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bia/Documents/feup/DA/ProjectDA/main.cpp -o CMakeFiles/untitled.dir/main.cpp.s

CMakeFiles/untitled.dir/graph.cpp.o: CMakeFiles/untitled.dir/flags.make
CMakeFiles/untitled.dir/graph.cpp.o: /home/bia/Documents/feup/DA/ProjectDA/graph.cpp
CMakeFiles/untitled.dir/graph.cpp.o: CMakeFiles/untitled.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/untitled.dir/graph.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/untitled.dir/graph.cpp.o -MF CMakeFiles/untitled.dir/graph.cpp.o.d -o CMakeFiles/untitled.dir/graph.cpp.o -c /home/bia/Documents/feup/DA/ProjectDA/graph.cpp

CMakeFiles/untitled.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/untitled.dir/graph.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bia/Documents/feup/DA/ProjectDA/graph.cpp > CMakeFiles/untitled.dir/graph.cpp.i

CMakeFiles/untitled.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/graph.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bia/Documents/feup/DA/ProjectDA/graph.cpp -o CMakeFiles/untitled.dir/graph.cpp.s

CMakeFiles/untitled.dir/batch.cpp.o: CMakeFiles/untitled.dir/flags.make
CMakeFiles/untitled.dir/batch.cpp.o: /home/bia/Documents/feup/DA/ProjectDA/batch.cpp
CMakeFiles/untitled.dir/batch.cpp.o: CMakeFiles/untitled.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/untitled.dir/batch.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/untitled.dir/batch.cpp.o -MF CMakeFiles/untitled.dir/batch.cpp.o.d -o CMakeFiles/untitled.dir/batch.cpp.o -c /home/bia/Documents/feup/DA/ProjectDA/batch.cpp

CMakeFiles/untitled.dir/batch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/untitled.dir/batch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bia/Documents/feup/DA/ProjectDA/batch.cpp > CMakeFiles/untitled.dir/batch.cpp.i

CMakeFiles/untitled.dir/batch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/batch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bia/Documents/feup/DA/ProjectDA/batch.cpp -o CMakeFiles/untitled.dir/batch.cpp.s

CMakeFiles/untitled.dir/dijkstra.cpp.o: CMakeFiles/untitled.dir/flags.make
CMakeFiles/untitled.dir/dijkstra.cpp.o: /home/bia/Documents/feup/DA/ProjectDA/dijkstra.cpp
CMakeFiles/untitled.dir/dijkstra.cpp.o: CMakeFiles/untitled.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/untitled.dir/dijkstra.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/untitled.dir/dijkstra.cpp.o -MF CMakeFiles/untitled.dir/dijkstra.cpp.o.d -o CMakeFiles/untitled.dir/dijkstra.cpp.o -c /home/bia/Documents/feup/DA/ProjectDA/dijkstra.cpp

CMakeFiles/untitled.dir/dijkstra.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/untitled.dir/dijkstra.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bia/Documents/feup/DA/ProjectDA/dijkstra.cpp > CMakeFiles/untitled.dir/dijkstra.cpp.i

CMakeFiles/untitled.dir/dijkstra.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/dijkstra.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bia/Documents/feup/DA/ProjectDA/dijkstra.cpp -o CMakeFiles/untitled.dir/dijkstra.cpp.s

CMakeFiles/untitled.dir/dijkstra-restricted.cpp.o: CMakeFiles/untitled.dir/flags.make
CMakeFiles/untitled.dir/dijkstra-restricted.cpp.o: /home/bia/Documents/feup/DA/ProjectDA/dijkstra-restricted.cpp
CMakeFiles/untitled.dir/dijkstra-restricted.cpp.o: CMakeFiles/untitled.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/untitled.dir/dijkstra-restricted.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/untitled.dir/dijkstra-restricted.cpp.o -MF CMakeFiles/untitled.dir/dijkstra-restricted.cpp.o.d -o CMakeFiles/untitled.dir/dijkstra-restricted.cpp.o -c /home/bia/Documents/feup/DA/ProjectDA/dijkstra-restricted.cpp

CMakeFiles/untitled.dir/dijkstra-restricted.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/untitled.dir/dijkstra-restricted.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bia/Documents/feup/DA/ProjectDA/dijkstra-restricted.cpp > CMakeFiles/untitled.dir/dijkstra-restricted.cpp.i

CMakeFiles/untitled.dir/dijkstra-restricted.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/dijkstra-restricted.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bia/Documents/feup/DA/ProjectDA/dijkstra-restricted.cpp -o CMakeFiles/untitled.dir/dijkstra-restricted.cpp.s

# Object files for target untitled
untitled_OBJECTS = \
"CMakeFiles/untitled.dir/main.cpp.o" \
"CMakeFiles/untitled.dir/graph.cpp.o" \
"CMakeFiles/untitled.dir/batch.cpp.o" \
"CMakeFiles/untitled.dir/dijkstra.cpp.o" \
"CMakeFiles/untitled.dir/dijkstra-restricted.cpp.o"

# External object files for target untitled
untitled_EXTERNAL_OBJECTS =

untitled: CMakeFiles/untitled.dir/main.cpp.o
untitled: CMakeFiles/untitled.dir/graph.cpp.o
untitled: CMakeFiles/untitled.dir/batch.cpp.o
untitled: CMakeFiles/untitled.dir/dijkstra.cpp.o
untitled: CMakeFiles/untitled.dir/dijkstra-restricted.cpp.o
untitled: CMakeFiles/untitled.dir/build.make
untitled: CMakeFiles/untitled.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable untitled"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled.dir/build: untitled
.PHONY : CMakeFiles/untitled.dir/build

CMakeFiles/untitled.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled.dir/clean

CMakeFiles/untitled.dir/depend:
	cd /home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bia/Documents/feup/DA/ProjectDA /home/bia/Documents/feup/DA/ProjectDA /home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug /home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug /home/bia/Documents/feup/DA/ProjectDA/cmake-build-debug/CMakeFiles/untitled.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/untitled.dir/depend

