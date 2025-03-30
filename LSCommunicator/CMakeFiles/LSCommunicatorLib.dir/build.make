# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.23.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.23.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alex_fly/Downloads/fork-in-lsp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alex_fly/Downloads/fork-in-lsp

# Include any dependencies generated for this target.
include lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/progress.make

# Include the compile flags for this target's objects.
include lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/flags.make

lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.o: lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/flags.make
lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.o: lib/LSCommunicator/LSCommunicator.cpp
lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.o: lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alex_fly/Downloads/fork-in-lsp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.o"
	cd /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.o -MF CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.o.d -o CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.o -c /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator/LSCommunicator.cpp

lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.i"
	cd /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator/LSCommunicator.cpp > CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.i

lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.s"
	cd /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator/LSCommunicator.cpp -o CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.s

# Object files for target LSCommunicatorLib
LSCommunicatorLib_OBJECTS = \
"CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.o"

# External object files for target LSCommunicatorLib
LSCommunicatorLib_EXTERNAL_OBJECTS =

lib/LSCommunicator/libLSCommunicatorLib.a: lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/LSCommunicator.cpp.o
lib/LSCommunicator/libLSCommunicatorLib.a: lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/build.make
lib/LSCommunicator/libLSCommunicatorLib.a: lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alex_fly/Downloads/fork-in-lsp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libLSCommunicatorLib.a"
	cd /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator && $(CMAKE_COMMAND) -P CMakeFiles/LSCommunicatorLib.dir/cmake_clean_target.cmake
	cd /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LSCommunicatorLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/build: lib/LSCommunicator/libLSCommunicatorLib.a
.PHONY : lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/build

lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/clean:
	cd /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator && $(CMAKE_COMMAND) -P CMakeFiles/LSCommunicatorLib.dir/cmake_clean.cmake
.PHONY : lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/clean

lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/depend:
	cd /Users/alex_fly/Downloads/fork-in-lsp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alex_fly/Downloads/fork-in-lsp /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator /Users/alex_fly/Downloads/fork-in-lsp /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator /Users/alex_fly/Downloads/fork-in-lsp/lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/LSCommunicator/CMakeFiles/LSCommunicatorLib.dir/depend

