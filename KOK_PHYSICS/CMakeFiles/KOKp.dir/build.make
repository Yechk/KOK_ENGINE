# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1

# Include any dependencies generated for this target.
include KOK_PHYSICS/CMakeFiles/KOKp.dir/depend.make

# Include the progress variables for this target.
include KOK_PHYSICS/CMakeFiles/KOKp.dir/progress.make

# Include the compile flags for this target's objects.
include KOK_PHYSICS/CMakeFiles/KOKp.dir/flags.make

KOK_PHYSICS/CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.o: KOK_PHYSICS/CMakeFiles/KOKp.dir/flags.make
KOK_PHYSICS/CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.o: KOK_PHYSICS/src/KOK_PhysicsContext.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object KOK_PHYSICS/CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.o"
	cd /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.o -c /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS/src/KOK_PhysicsContext.cpp

KOK_PHYSICS/CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.i"
	cd /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS/src/KOK_PhysicsContext.cpp > CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.i

KOK_PHYSICS/CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.s"
	cd /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS/src/KOK_PhysicsContext.cpp -o CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.s

# Object files for target KOKp
KOKp_OBJECTS = \
"CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.o"

# External object files for target KOKp
KOKp_EXTERNAL_OBJECTS =

KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/CMakeFiles/KOKp.dir/src/KOK_PhysicsContext.cpp.o
KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/CMakeFiles/KOKp.dir/build.make
KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysX_static_64.a
KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXCommon_static_64.a
KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXCharacterKinematic_static_64.a
KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXCooking_static_64.a
KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXExtensions_static_64.a
KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXFoundation_static_64.a
KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXPvdSDK_static_64.a
KOK_PHYSICS/libKOKp.so: KOK_PHYSICS/CMakeFiles/KOKp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libKOKp.so"
	cd /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KOKp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
KOK_PHYSICS/CMakeFiles/KOKp.dir/build: KOK_PHYSICS/libKOKp.so

.PHONY : KOK_PHYSICS/CMakeFiles/KOKp.dir/build

KOK_PHYSICS/CMakeFiles/KOKp.dir/clean:
	cd /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS && $(CMAKE_COMMAND) -P CMakeFiles/KOKp.dir/cmake_clean.cmake
.PHONY : KOK_PHYSICS/CMakeFiles/KOKp.dir/clean

KOK_PHYSICS/CMakeFiles/KOKp.dir/depend:
	cd /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1 /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1 /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_PHYSICS/CMakeFiles/KOKp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : KOK_PHYSICS/CMakeFiles/KOKp.dir/depend

