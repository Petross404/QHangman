# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\petros\QHangman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\petros\QHangman\build

# Utility rule file for qhangman_autogen.

# Include the progress variables for this target.
include CMakeFiles\qhangman_autogen.dir\progress.make

CMakeFiles\qhangman_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\petros\QHangman\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target qhangman"
	echo >nul && "C:\Program Files\CMake\bin\cmake.exe" -E cmake_autogen C:/Users/petros/QHangman/build/CMakeFiles/qhangman_autogen.dir/AutogenInfo.cmake Debug

qhangman_autogen: CMakeFiles\qhangman_autogen
qhangman_autogen: CMakeFiles\qhangman_autogen.dir\build.make

.PHONY : qhangman_autogen

# Rule to build all files generated by this target.
CMakeFiles\qhangman_autogen.dir\build: qhangman_autogen

.PHONY : CMakeFiles\qhangman_autogen.dir\build

CMakeFiles\qhangman_autogen.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\qhangman_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles\qhangman_autogen.dir\clean

CMakeFiles\qhangman_autogen.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\petros\QHangman C:\Users\petros\QHangman C:\Users\petros\QHangman\build C:\Users\petros\QHangman\build C:\Users\petros\QHangman\build\CMakeFiles\qhangman_autogen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\qhangman_autogen.dir\depend
