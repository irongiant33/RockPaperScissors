# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/irongiant/RockPaperScissors

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/RockPaperScissors/build

# Include any dependencies generated for this target.
include CMakeFiles/RockPaperScissors_code.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RockPaperScissors_code.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RockPaperScissors_code.dir/flags.make

CMakeFiles/RockPaperScissors_code.dir/src/play.c.o: CMakeFiles/RockPaperScissors_code.dir/flags.make
CMakeFiles/RockPaperScissors_code.dir/src/play.c.o: ../src/play.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/RockPaperScissors/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RockPaperScissors_code.dir/src/play.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/RockPaperScissors_code.dir/src/play.c.o   -c /home/irongiant/RockPaperScissors/src/play.c

CMakeFiles/RockPaperScissors_code.dir/src/play.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RockPaperScissors_code.dir/src/play.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/RockPaperScissors/src/play.c > CMakeFiles/RockPaperScissors_code.dir/src/play.c.i

CMakeFiles/RockPaperScissors_code.dir/src/play.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RockPaperScissors_code.dir/src/play.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/RockPaperScissors/src/play.c -o CMakeFiles/RockPaperScissors_code.dir/src/play.c.s

CMakeFiles/RockPaperScissors_code.dir/src/bots.c.o: CMakeFiles/RockPaperScissors_code.dir/flags.make
CMakeFiles/RockPaperScissors_code.dir/src/bots.c.o: ../src/bots.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/RockPaperScissors/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/RockPaperScissors_code.dir/src/bots.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/RockPaperScissors_code.dir/src/bots.c.o   -c /home/irongiant/RockPaperScissors/src/bots.c

CMakeFiles/RockPaperScissors_code.dir/src/bots.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RockPaperScissors_code.dir/src/bots.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/RockPaperScissors/src/bots.c > CMakeFiles/RockPaperScissors_code.dir/src/bots.c.i

CMakeFiles/RockPaperScissors_code.dir/src/bots.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RockPaperScissors_code.dir/src/bots.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/RockPaperScissors/src/bots.c -o CMakeFiles/RockPaperScissors_code.dir/src/bots.c.s

CMakeFiles/RockPaperScissors_code.dir/src/display.c.o: CMakeFiles/RockPaperScissors_code.dir/flags.make
CMakeFiles/RockPaperScissors_code.dir/src/display.c.o: ../src/display.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/RockPaperScissors/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/RockPaperScissors_code.dir/src/display.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/RockPaperScissors_code.dir/src/display.c.o   -c /home/irongiant/RockPaperScissors/src/display.c

CMakeFiles/RockPaperScissors_code.dir/src/display.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RockPaperScissors_code.dir/src/display.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/RockPaperScissors/src/display.c > CMakeFiles/RockPaperScissors_code.dir/src/display.c.i

CMakeFiles/RockPaperScissors_code.dir/src/display.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RockPaperScissors_code.dir/src/display.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/RockPaperScissors/src/display.c -o CMakeFiles/RockPaperScissors_code.dir/src/display.c.s

# Object files for target RockPaperScissors_code
RockPaperScissors_code_OBJECTS = \
"CMakeFiles/RockPaperScissors_code.dir/src/play.c.o" \
"CMakeFiles/RockPaperScissors_code.dir/src/bots.c.o" \
"CMakeFiles/RockPaperScissors_code.dir/src/display.c.o"

# External object files for target RockPaperScissors_code
RockPaperScissors_code_EXTERNAL_OBJECTS =

libRockPaperScissors_code.so: CMakeFiles/RockPaperScissors_code.dir/src/play.c.o
libRockPaperScissors_code.so: CMakeFiles/RockPaperScissors_code.dir/src/bots.c.o
libRockPaperScissors_code.so: CMakeFiles/RockPaperScissors_code.dir/src/display.c.o
libRockPaperScissors_code.so: CMakeFiles/RockPaperScissors_code.dir/build.make
libRockPaperScissors_code.so: CMakeFiles/RockPaperScissors_code.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/RockPaperScissors/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C shared library libRockPaperScissors_code.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RockPaperScissors_code.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RockPaperScissors_code.dir/build: libRockPaperScissors_code.so

.PHONY : CMakeFiles/RockPaperScissors_code.dir/build

CMakeFiles/RockPaperScissors_code.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RockPaperScissors_code.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RockPaperScissors_code.dir/clean

CMakeFiles/RockPaperScissors_code.dir/depend:
	cd /home/irongiant/RockPaperScissors/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/RockPaperScissors /home/irongiant/RockPaperScissors /home/irongiant/RockPaperScissors/build /home/irongiant/RockPaperScissors/build /home/irongiant/RockPaperScissors/build/CMakeFiles/RockPaperScissors_code.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RockPaperScissors_code.dir/depend

