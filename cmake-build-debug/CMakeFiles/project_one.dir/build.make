# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Randall Henderson\project-one"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Randall Henderson\project-one\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/project_one.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project_one.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project_one.dir/flags.make

CMakeFiles/project_one.dir/src/main.cpp.obj: CMakeFiles/project_one.dir/flags.make
CMakeFiles/project_one.dir/src/main.cpp.obj: CMakeFiles/project_one.dir/includes_CXX.rsp
CMakeFiles/project_one.dir/src/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Randall Henderson\project-one\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project_one.dir/src/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\project_one.dir\src\main.cpp.obj -c "C:\Users\Randall Henderson\project-one\src\main.cpp"

CMakeFiles/project_one.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_one.dir/src/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Randall Henderson\project-one\src\main.cpp" > CMakeFiles\project_one.dir\src\main.cpp.i

CMakeFiles/project_one.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_one.dir/src/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Randall Henderson\project-one\src\main.cpp" -o CMakeFiles\project_one.dir\src\main.cpp.s

CMakeFiles/project_one.dir/src/mainwindow.cpp.obj: CMakeFiles/project_one.dir/flags.make
CMakeFiles/project_one.dir/src/mainwindow.cpp.obj: CMakeFiles/project_one.dir/includes_CXX.rsp
CMakeFiles/project_one.dir/src/mainwindow.cpp.obj: ../src/mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Randall Henderson\project-one\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project_one.dir/src/mainwindow.cpp.obj"
	C:\PROGRA~1\MINGW-~1\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\project_one.dir\src\mainwindow.cpp.obj -c "C:\Users\Randall Henderson\project-one\src\mainwindow.cpp"

CMakeFiles/project_one.dir/src/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_one.dir/src/mainwindow.cpp.i"
	C:\PROGRA~1\MINGW-~1\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Randall Henderson\project-one\src\mainwindow.cpp" > CMakeFiles\project_one.dir\src\mainwindow.cpp.i

CMakeFiles/project_one.dir/src/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_one.dir/src/mainwindow.cpp.s"
	C:\PROGRA~1\MINGW-~1\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Randall Henderson\project-one\src\mainwindow.cpp" -o CMakeFiles\project_one.dir\src\mainwindow.cpp.s

# Object files for target project_one
project_one_OBJECTS = \
"CMakeFiles/project_one.dir/src/main.cpp.obj" \
"CMakeFiles/project_one.dir/src/mainwindow.cpp.obj"

# External object files for target project_one
project_one_EXTERNAL_OBJECTS =

project_one.exe: CMakeFiles/project_one.dir/src/main.cpp.obj
project_one.exe: CMakeFiles/project_one.dir/src/mainwindow.cpp.obj
project_one.exe: CMakeFiles/project_one.dir/build.make
project_one.exe: CMakeFiles/project_one.dir/linklibs.rsp
project_one.exe: CMakeFiles/project_one.dir/objects1.rsp
project_one.exe: CMakeFiles/project_one.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Randall Henderson\project-one\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable project_one.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\project_one.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project_one.dir/build: project_one.exe

.PHONY : CMakeFiles/project_one.dir/build

CMakeFiles/project_one.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\project_one.dir\cmake_clean.cmake
.PHONY : CMakeFiles/project_one.dir/clean

CMakeFiles/project_one.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Randall Henderson\project-one" "C:\Users\Randall Henderson\project-one" "C:\Users\Randall Henderson\project-one\cmake-build-debug" "C:\Users\Randall Henderson\project-one\cmake-build-debug" "C:\Users\Randall Henderson\project-one\cmake-build-debug\CMakeFiles\project_one.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/project_one.dir/depend

