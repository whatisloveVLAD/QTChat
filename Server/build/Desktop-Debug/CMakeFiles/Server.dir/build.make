# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/vlad/projects/qtProjects/chat/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/Server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server.dir/flags.make

Server_autogen/timestamp: /usr/lib/qt5/bin/moc
Server_autogen/timestamp: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target Server"
	/usr/bin/cmake -E cmake_autogen /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/CMakeFiles/Server_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/Server_autogen/timestamp

CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o: Server_autogen/mocs_compilation.cpp
CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o -MF CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o -c /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/Server_autogen/mocs_compilation.cpp

CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/Server_autogen/mocs_compilation.cpp > CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.i

CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/Server_autogen/mocs_compilation.cpp -o CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.s

CMakeFiles/Server.dir/main.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/main.cpp.o: /home/vlad/projects/qtProjects/chat/Server/main.cpp
CMakeFiles/Server.dir/main.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Server.dir/main.cpp.o"
	/usr/bin/g++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/main.cpp.o -MF CMakeFiles/Server.dir/main.cpp.o.d -o CMakeFiles/Server.dir/main.cpp.o -c /home/vlad/projects/qtProjects/chat/Server/main.cpp

CMakeFiles/Server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Server.dir/main.cpp.i"
	/usr/bin/g++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vlad/projects/qtProjects/chat/Server/main.cpp > CMakeFiles/Server.dir/main.cpp.i

CMakeFiles/Server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Server.dir/main.cpp.s"
	/usr/bin/g++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vlad/projects/qtProjects/chat/Server/main.cpp -o CMakeFiles/Server.dir/main.cpp.s

CMakeFiles/Server.dir/server.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/server.cpp.o: /home/vlad/projects/qtProjects/chat/Server/server.cpp
CMakeFiles/Server.dir/server.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Server.dir/server.cpp.o"
	/usr/bin/g++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/server.cpp.o -MF CMakeFiles/Server.dir/server.cpp.o.d -o CMakeFiles/Server.dir/server.cpp.o -c /home/vlad/projects/qtProjects/chat/Server/server.cpp

CMakeFiles/Server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Server.dir/server.cpp.i"
	/usr/bin/g++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vlad/projects/qtProjects/chat/Server/server.cpp > CMakeFiles/Server.dir/server.cpp.i

CMakeFiles/Server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Server.dir/server.cpp.s"
	/usr/bin/g++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vlad/projects/qtProjects/chat/Server/server.cpp -o CMakeFiles/Server.dir/server.cpp.s

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/Server.dir/main.cpp.o" \
"CMakeFiles/Server.dir/server.cpp.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server: CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o
Server: CMakeFiles/Server.dir/main.cpp.o
Server: CMakeFiles/Server.dir/server.cpp.o
Server: CMakeFiles/Server.dir/build.make
Server: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.15.13
Server: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.13
Server: CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server.dir/build: Server
.PHONY : CMakeFiles/Server.dir/build

CMakeFiles/Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server.dir/clean

CMakeFiles/Server.dir/depend: Server_autogen/timestamp
	cd /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vlad/projects/qtProjects/chat/Server /home/vlad/projects/qtProjects/chat/Server /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug /home/vlad/projects/qtProjects/chat/Server/build/Desktop-Debug/CMakeFiles/Server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Server.dir/depend

