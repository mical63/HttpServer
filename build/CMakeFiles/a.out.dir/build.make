# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/mical/HttpSevver/HttpServer-C

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mical/HttpSevver/HttpServer-C/build

# Include any dependencies generated for this target.
include CMakeFiles/a.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/a.out.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/a.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a.out.dir/flags.make

CMakeFiles/a.out.dir/src/Buffer.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/Buffer.c.o: ../src/Buffer.c
CMakeFiles/a.out.dir/src/Buffer.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/a.out.dir/src/Buffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/Buffer.c.o -MF CMakeFiles/a.out.dir/src/Buffer.c.o.d -o CMakeFiles/a.out.dir/src/Buffer.c.o -c /home/mical/HttpSevver/HttpServer-C/src/Buffer.c

CMakeFiles/a.out.dir/src/Buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/Buffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/Buffer.c > CMakeFiles/a.out.dir/src/Buffer.c.i

CMakeFiles/a.out.dir/src/Buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/Buffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/Buffer.c -o CMakeFiles/a.out.dir/src/Buffer.c.s

CMakeFiles/a.out.dir/src/ChannelMap.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/ChannelMap.c.o: ../src/ChannelMap.c
CMakeFiles/a.out.dir/src/ChannelMap.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/a.out.dir/src/ChannelMap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/ChannelMap.c.o -MF CMakeFiles/a.out.dir/src/ChannelMap.c.o.d -o CMakeFiles/a.out.dir/src/ChannelMap.c.o -c /home/mical/HttpSevver/HttpServer-C/src/ChannelMap.c

CMakeFiles/a.out.dir/src/ChannelMap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/ChannelMap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/ChannelMap.c > CMakeFiles/a.out.dir/src/ChannelMap.c.i

CMakeFiles/a.out.dir/src/ChannelMap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/ChannelMap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/ChannelMap.c -o CMakeFiles/a.out.dir/src/ChannelMap.c.s

CMakeFiles/a.out.dir/src/EpollDispatcher.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/EpollDispatcher.c.o: ../src/EpollDispatcher.c
CMakeFiles/a.out.dir/src/EpollDispatcher.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/a.out.dir/src/EpollDispatcher.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/EpollDispatcher.c.o -MF CMakeFiles/a.out.dir/src/EpollDispatcher.c.o.d -o CMakeFiles/a.out.dir/src/EpollDispatcher.c.o -c /home/mical/HttpSevver/HttpServer-C/src/EpollDispatcher.c

CMakeFiles/a.out.dir/src/EpollDispatcher.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/EpollDispatcher.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/EpollDispatcher.c > CMakeFiles/a.out.dir/src/EpollDispatcher.c.i

CMakeFiles/a.out.dir/src/EpollDispatcher.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/EpollDispatcher.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/EpollDispatcher.c -o CMakeFiles/a.out.dir/src/EpollDispatcher.c.s

CMakeFiles/a.out.dir/src/EventLoop.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/EventLoop.c.o: ../src/EventLoop.c
CMakeFiles/a.out.dir/src/EventLoop.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/a.out.dir/src/EventLoop.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/EventLoop.c.o -MF CMakeFiles/a.out.dir/src/EventLoop.c.o.d -o CMakeFiles/a.out.dir/src/EventLoop.c.o -c /home/mical/HttpSevver/HttpServer-C/src/EventLoop.c

CMakeFiles/a.out.dir/src/EventLoop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/EventLoop.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/EventLoop.c > CMakeFiles/a.out.dir/src/EventLoop.c.i

CMakeFiles/a.out.dir/src/EventLoop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/EventLoop.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/EventLoop.c -o CMakeFiles/a.out.dir/src/EventLoop.c.s

CMakeFiles/a.out.dir/src/HttpRequest.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/HttpRequest.c.o: ../src/HttpRequest.c
CMakeFiles/a.out.dir/src/HttpRequest.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/a.out.dir/src/HttpRequest.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/HttpRequest.c.o -MF CMakeFiles/a.out.dir/src/HttpRequest.c.o.d -o CMakeFiles/a.out.dir/src/HttpRequest.c.o -c /home/mical/HttpSevver/HttpServer-C/src/HttpRequest.c

CMakeFiles/a.out.dir/src/HttpRequest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/HttpRequest.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/HttpRequest.c > CMakeFiles/a.out.dir/src/HttpRequest.c.i

CMakeFiles/a.out.dir/src/HttpRequest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/HttpRequest.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/HttpRequest.c -o CMakeFiles/a.out.dir/src/HttpRequest.c.s

CMakeFiles/a.out.dir/src/HttpResponse.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/HttpResponse.c.o: ../src/HttpResponse.c
CMakeFiles/a.out.dir/src/HttpResponse.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/a.out.dir/src/HttpResponse.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/HttpResponse.c.o -MF CMakeFiles/a.out.dir/src/HttpResponse.c.o.d -o CMakeFiles/a.out.dir/src/HttpResponse.c.o -c /home/mical/HttpSevver/HttpServer-C/src/HttpResponse.c

CMakeFiles/a.out.dir/src/HttpResponse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/HttpResponse.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/HttpResponse.c > CMakeFiles/a.out.dir/src/HttpResponse.c.i

CMakeFiles/a.out.dir/src/HttpResponse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/HttpResponse.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/HttpResponse.c -o CMakeFiles/a.out.dir/src/HttpResponse.c.s

CMakeFiles/a.out.dir/src/PollDispatcher.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/PollDispatcher.c.o: ../src/PollDispatcher.c
CMakeFiles/a.out.dir/src/PollDispatcher.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/a.out.dir/src/PollDispatcher.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/PollDispatcher.c.o -MF CMakeFiles/a.out.dir/src/PollDispatcher.c.o.d -o CMakeFiles/a.out.dir/src/PollDispatcher.c.o -c /home/mical/HttpSevver/HttpServer-C/src/PollDispatcher.c

CMakeFiles/a.out.dir/src/PollDispatcher.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/PollDispatcher.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/PollDispatcher.c > CMakeFiles/a.out.dir/src/PollDispatcher.c.i

CMakeFiles/a.out.dir/src/PollDispatcher.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/PollDispatcher.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/PollDispatcher.c -o CMakeFiles/a.out.dir/src/PollDispatcher.c.s

CMakeFiles/a.out.dir/src/SelectDispatcher.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/SelectDispatcher.c.o: ../src/SelectDispatcher.c
CMakeFiles/a.out.dir/src/SelectDispatcher.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/a.out.dir/src/SelectDispatcher.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/SelectDispatcher.c.o -MF CMakeFiles/a.out.dir/src/SelectDispatcher.c.o.d -o CMakeFiles/a.out.dir/src/SelectDispatcher.c.o -c /home/mical/HttpSevver/HttpServer-C/src/SelectDispatcher.c

CMakeFiles/a.out.dir/src/SelectDispatcher.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/SelectDispatcher.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/SelectDispatcher.c > CMakeFiles/a.out.dir/src/SelectDispatcher.c.i

CMakeFiles/a.out.dir/src/SelectDispatcher.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/SelectDispatcher.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/SelectDispatcher.c -o CMakeFiles/a.out.dir/src/SelectDispatcher.c.s

CMakeFiles/a.out.dir/src/TcpConnection.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/TcpConnection.c.o: ../src/TcpConnection.c
CMakeFiles/a.out.dir/src/TcpConnection.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/a.out.dir/src/TcpConnection.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/TcpConnection.c.o -MF CMakeFiles/a.out.dir/src/TcpConnection.c.o.d -o CMakeFiles/a.out.dir/src/TcpConnection.c.o -c /home/mical/HttpSevver/HttpServer-C/src/TcpConnection.c

CMakeFiles/a.out.dir/src/TcpConnection.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/TcpConnection.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/TcpConnection.c > CMakeFiles/a.out.dir/src/TcpConnection.c.i

CMakeFiles/a.out.dir/src/TcpConnection.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/TcpConnection.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/TcpConnection.c -o CMakeFiles/a.out.dir/src/TcpConnection.c.s

CMakeFiles/a.out.dir/src/TcpServer.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/TcpServer.c.o: ../src/TcpServer.c
CMakeFiles/a.out.dir/src/TcpServer.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/a.out.dir/src/TcpServer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/TcpServer.c.o -MF CMakeFiles/a.out.dir/src/TcpServer.c.o.d -o CMakeFiles/a.out.dir/src/TcpServer.c.o -c /home/mical/HttpSevver/HttpServer-C/src/TcpServer.c

CMakeFiles/a.out.dir/src/TcpServer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/TcpServer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/TcpServer.c > CMakeFiles/a.out.dir/src/TcpServer.c.i

CMakeFiles/a.out.dir/src/TcpServer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/TcpServer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/TcpServer.c -o CMakeFiles/a.out.dir/src/TcpServer.c.s

CMakeFiles/a.out.dir/src/ThreadPool.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/ThreadPool.c.o: ../src/ThreadPool.c
CMakeFiles/a.out.dir/src/ThreadPool.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/a.out.dir/src/ThreadPool.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/ThreadPool.c.o -MF CMakeFiles/a.out.dir/src/ThreadPool.c.o.d -o CMakeFiles/a.out.dir/src/ThreadPool.c.o -c /home/mical/HttpSevver/HttpServer-C/src/ThreadPool.c

CMakeFiles/a.out.dir/src/ThreadPool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/ThreadPool.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/ThreadPool.c > CMakeFiles/a.out.dir/src/ThreadPool.c.i

CMakeFiles/a.out.dir/src/ThreadPool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/ThreadPool.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/ThreadPool.c -o CMakeFiles/a.out.dir/src/ThreadPool.c.s

CMakeFiles/a.out.dir/src/WorkerThread.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/WorkerThread.c.o: ../src/WorkerThread.c
CMakeFiles/a.out.dir/src/WorkerThread.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/a.out.dir/src/WorkerThread.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/WorkerThread.c.o -MF CMakeFiles/a.out.dir/src/WorkerThread.c.o.d -o CMakeFiles/a.out.dir/src/WorkerThread.c.o -c /home/mical/HttpSevver/HttpServer-C/src/WorkerThread.c

CMakeFiles/a.out.dir/src/WorkerThread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/WorkerThread.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/WorkerThread.c > CMakeFiles/a.out.dir/src/WorkerThread.c.i

CMakeFiles/a.out.dir/src/WorkerThread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/WorkerThread.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/WorkerThread.c -o CMakeFiles/a.out.dir/src/WorkerThread.c.s

CMakeFiles/a.out.dir/src/channel.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/channel.c.o: ../src/channel.c
CMakeFiles/a.out.dir/src/channel.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/a.out.dir/src/channel.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/channel.c.o -MF CMakeFiles/a.out.dir/src/channel.c.o.d -o CMakeFiles/a.out.dir/src/channel.c.o -c /home/mical/HttpSevver/HttpServer-C/src/channel.c

CMakeFiles/a.out.dir/src/channel.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/channel.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/channel.c > CMakeFiles/a.out.dir/src/channel.c.i

CMakeFiles/a.out.dir/src/channel.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/channel.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/channel.c -o CMakeFiles/a.out.dir/src/channel.c.s

CMakeFiles/a.out.dir/src/main.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/src/main.c.o: ../src/main.c
CMakeFiles/a.out.dir/src/main.c.o: CMakeFiles/a.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/a.out.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/a.out.dir/src/main.c.o -MF CMakeFiles/a.out.dir/src/main.c.o.d -o CMakeFiles/a.out.dir/src/main.c.o -c /home/mical/HttpSevver/HttpServer-C/src/main.c

CMakeFiles/a.out.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mical/HttpSevver/HttpServer-C/src/main.c > CMakeFiles/a.out.dir/src/main.c.i

CMakeFiles/a.out.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mical/HttpSevver/HttpServer-C/src/main.c -o CMakeFiles/a.out.dir/src/main.c.s

# Object files for target a.out
a_out_OBJECTS = \
"CMakeFiles/a.out.dir/src/Buffer.c.o" \
"CMakeFiles/a.out.dir/src/ChannelMap.c.o" \
"CMakeFiles/a.out.dir/src/EpollDispatcher.c.o" \
"CMakeFiles/a.out.dir/src/EventLoop.c.o" \
"CMakeFiles/a.out.dir/src/HttpRequest.c.o" \
"CMakeFiles/a.out.dir/src/HttpResponse.c.o" \
"CMakeFiles/a.out.dir/src/PollDispatcher.c.o" \
"CMakeFiles/a.out.dir/src/SelectDispatcher.c.o" \
"CMakeFiles/a.out.dir/src/TcpConnection.c.o" \
"CMakeFiles/a.out.dir/src/TcpServer.c.o" \
"CMakeFiles/a.out.dir/src/ThreadPool.c.o" \
"CMakeFiles/a.out.dir/src/WorkerThread.c.o" \
"CMakeFiles/a.out.dir/src/channel.c.o" \
"CMakeFiles/a.out.dir/src/main.c.o"

# External object files for target a.out
a_out_EXTERNAL_OBJECTS =

a.out: CMakeFiles/a.out.dir/src/Buffer.c.o
a.out: CMakeFiles/a.out.dir/src/ChannelMap.c.o
a.out: CMakeFiles/a.out.dir/src/EpollDispatcher.c.o
a.out: CMakeFiles/a.out.dir/src/EventLoop.c.o
a.out: CMakeFiles/a.out.dir/src/HttpRequest.c.o
a.out: CMakeFiles/a.out.dir/src/HttpResponse.c.o
a.out: CMakeFiles/a.out.dir/src/PollDispatcher.c.o
a.out: CMakeFiles/a.out.dir/src/SelectDispatcher.c.o
a.out: CMakeFiles/a.out.dir/src/TcpConnection.c.o
a.out: CMakeFiles/a.out.dir/src/TcpServer.c.o
a.out: CMakeFiles/a.out.dir/src/ThreadPool.c.o
a.out: CMakeFiles/a.out.dir/src/WorkerThread.c.o
a.out: CMakeFiles/a.out.dir/src/channel.c.o
a.out: CMakeFiles/a.out.dir/src/main.c.o
a.out: CMakeFiles/a.out.dir/build.make
a.out: CMakeFiles/a.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mical/HttpSevver/HttpServer-C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking C executable a.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a.out.dir/build: a.out
.PHONY : CMakeFiles/a.out.dir/build

CMakeFiles/a.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a.out.dir/clean

CMakeFiles/a.out.dir/depend:
	cd /home/mical/HttpSevver/HttpServer-C/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mical/HttpSevver/HttpServer-C /home/mical/HttpSevver/HttpServer-C /home/mical/HttpSevver/HttpServer-C/build /home/mical/HttpSevver/HttpServer-C/build /home/mical/HttpSevver/HttpServer-C/build/CMakeFiles/a.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/a.out.dir/depend

