# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/junk_chuan/CLionProjects/Network_Proj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/junk_chuan/CLionProjects/Network_Proj/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Network_Proj.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Network_Proj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Network_Proj.dir/flags.make

CMakeFiles/Network_Proj.dir/main.cpp.o: CMakeFiles/Network_Proj.dir/flags.make
CMakeFiles/Network_Proj.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/junk_chuan/CLionProjects/Network_Proj/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Network_Proj.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Network_Proj.dir/main.cpp.o -c /home/junk_chuan/CLionProjects/Network_Proj/main.cpp

CMakeFiles/Network_Proj.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Network_Proj.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/junk_chuan/CLionProjects/Network_Proj/main.cpp > CMakeFiles/Network_Proj.dir/main.cpp.i

CMakeFiles/Network_Proj.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Network_Proj.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/junk_chuan/CLionProjects/Network_Proj/main.cpp -o CMakeFiles/Network_Proj.dir/main.cpp.s

# Object files for target Network_Proj
Network_Proj_OBJECTS = \
"CMakeFiles/Network_Proj.dir/main.cpp.o"

# External object files for target Network_Proj
Network_Proj_EXTERNAL_OBJECTS =

Network_Proj: CMakeFiles/Network_Proj.dir/main.cpp.o
Network_Proj: CMakeFiles/Network_Proj.dir/build.make
Network_Proj: CMakeFiles/Network_Proj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/junk_chuan/CLionProjects/Network_Proj/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Network_Proj"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Network_Proj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Network_Proj.dir/build: Network_Proj

.PHONY : CMakeFiles/Network_Proj.dir/build

CMakeFiles/Network_Proj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Network_Proj.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Network_Proj.dir/clean

CMakeFiles/Network_Proj.dir/depend:
	cd /home/junk_chuan/CLionProjects/Network_Proj/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/junk_chuan/CLionProjects/Network_Proj /home/junk_chuan/CLionProjects/Network_Proj /home/junk_chuan/CLionProjects/Network_Proj/cmake-build-debug /home/junk_chuan/CLionProjects/Network_Proj/cmake-build-debug /home/junk_chuan/CLionProjects/Network_Proj/cmake-build-debug/CMakeFiles/Network_Proj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Network_Proj.dir/depend

