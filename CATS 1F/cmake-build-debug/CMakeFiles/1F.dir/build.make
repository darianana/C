# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\karpe\Desktop\C++\1F

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\karpe\Desktop\C++\1F\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/1F.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1F.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1F.dir/flags.make

CMakeFiles/1F.dir/main.cpp.obj: CMakeFiles/1F.dir/flags.make
CMakeFiles/1F.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\karpe\Desktop\C++\1F\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1F.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\1F.dir\main.cpp.obj -c C:\Users\karpe\Desktop\C++\1F\main.cpp

CMakeFiles/1F.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1F.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\karpe\Desktop\C++\1F\main.cpp > CMakeFiles\1F.dir\main.cpp.i

CMakeFiles/1F.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1F.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\karpe\Desktop\C++\1F\main.cpp -o CMakeFiles\1F.dir\main.cpp.s

# Object files for target 1F
1F_OBJECTS = \
"CMakeFiles/1F.dir/main.cpp.obj"

# External object files for target 1F
1F_EXTERNAL_OBJECTS =

1F.exe: CMakeFiles/1F.dir/main.cpp.obj
1F.exe: CMakeFiles/1F.dir/build.make
1F.exe: CMakeFiles/1F.dir/linklibs.rsp
1F.exe: CMakeFiles/1F.dir/objects1.rsp
1F.exe: CMakeFiles/1F.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\karpe\Desktop\C++\1F\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1F.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\1F.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1F.dir/build: 1F.exe

.PHONY : CMakeFiles/1F.dir/build

CMakeFiles/1F.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\1F.dir\cmake_clean.cmake
.PHONY : CMakeFiles/1F.dir/clean

CMakeFiles/1F.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\karpe\Desktop\C++\1F C:\Users\karpe\Desktop\C++\1F C:\Users\karpe\Desktop\C++\1F\cmake-build-debug C:\Users\karpe\Desktop\C++\1F\cmake-build-debug C:\Users\karpe\Desktop\C++\1F\cmake-build-debug\CMakeFiles\1F.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1F.dir/depend

