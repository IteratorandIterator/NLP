# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/cmake/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/test_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/test_1/build

# Include any dependencies generated for this target.
include CMakeFiles/Benchmark.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Benchmark.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Benchmark.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Benchmark.dir/flags.make

CMakeFiles/Benchmark.dir/Benchmark.cpp.o: CMakeFiles/Benchmark.dir/flags.make
CMakeFiles/Benchmark.dir/Benchmark.cpp.o: /root/test_1/Benchmark.cpp
CMakeFiles/Benchmark.dir/Benchmark.cpp.o: CMakeFiles/Benchmark.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/test_1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Benchmark.dir/Benchmark.cpp.o"
	/usr/local/clang/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Benchmark.dir/Benchmark.cpp.o -MF CMakeFiles/Benchmark.dir/Benchmark.cpp.o.d -o CMakeFiles/Benchmark.dir/Benchmark.cpp.o -c /root/test_1/Benchmark.cpp

CMakeFiles/Benchmark.dir/Benchmark.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Benchmark.dir/Benchmark.cpp.i"
	/usr/local/clang/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/test_1/Benchmark.cpp > CMakeFiles/Benchmark.dir/Benchmark.cpp.i

CMakeFiles/Benchmark.dir/Benchmark.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Benchmark.dir/Benchmark.cpp.s"
	/usr/local/clang/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/test_1/Benchmark.cpp -o CMakeFiles/Benchmark.dir/Benchmark.cpp.s

# Object files for target Benchmark
Benchmark_OBJECTS = \
"CMakeFiles/Benchmark.dir/Benchmark.cpp.o"

# External object files for target Benchmark
Benchmark_EXTERNAL_OBJECTS =

Benchmark: CMakeFiles/Benchmark.dir/Benchmark.cpp.o
Benchmark: CMakeFiles/Benchmark.dir/build.make
Benchmark: /usr/local/benchmark/lib/libbenchmark.a
Benchmark: /usr/local/tbb/lib/libtbb.so.12.8
Benchmark: CMakeFiles/Benchmark.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/test_1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Benchmark"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Benchmark.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Benchmark.dir/build: Benchmark
.PHONY : CMakeFiles/Benchmark.dir/build

CMakeFiles/Benchmark.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Benchmark.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Benchmark.dir/clean

CMakeFiles/Benchmark.dir/depend:
	cd /root/test_1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/test_1 /root/test_1 /root/test_1/build /root/test_1/build /root/test_1/build/CMakeFiles/Benchmark.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Benchmark.dir/depend

