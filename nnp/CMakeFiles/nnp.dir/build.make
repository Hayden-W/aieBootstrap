# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/hayden/dev/aieBootstrap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hayden/dev/aieBootstrap

# Include any dependencies generated for this target.
include nnp/CMakeFiles/nnp.dir/depend.make

# Include the progress variables for this target.
include nnp/CMakeFiles/nnp.dir/progress.make

# Include the compile flags for this target's objects.
include nnp/CMakeFiles/nnp.dir/flags.make

nnp/CMakeFiles/nnp.dir/main.cpp.o: nnp/CMakeFiles/nnp.dir/flags.make
nnp/CMakeFiles/nnp.dir/main.cpp.o: nnp/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hayden/dev/aieBootstrap/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object nnp/CMakeFiles/nnp.dir/main.cpp.o"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nnp.dir/main.cpp.o -c /home/hayden/dev/aieBootstrap/nnp/main.cpp

nnp/CMakeFiles/nnp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nnp.dir/main.cpp.i"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hayden/dev/aieBootstrap/nnp/main.cpp > CMakeFiles/nnp.dir/main.cpp.i

nnp/CMakeFiles/nnp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nnp.dir/main.cpp.s"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hayden/dev/aieBootstrap/nnp/main.cpp -o CMakeFiles/nnp.dir/main.cpp.s

nnp/CMakeFiles/nnp.dir/Controller.cpp.o: nnp/CMakeFiles/nnp.dir/flags.make
nnp/CMakeFiles/nnp.dir/Controller.cpp.o: nnp/Controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hayden/dev/aieBootstrap/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object nnp/CMakeFiles/nnp.dir/Controller.cpp.o"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nnp.dir/Controller.cpp.o -c /home/hayden/dev/aieBootstrap/nnp/Controller.cpp

nnp/CMakeFiles/nnp.dir/Controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nnp.dir/Controller.cpp.i"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hayden/dev/aieBootstrap/nnp/Controller.cpp > CMakeFiles/nnp.dir/Controller.cpp.i

nnp/CMakeFiles/nnp.dir/Controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nnp.dir/Controller.cpp.s"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hayden/dev/aieBootstrap/nnp/Controller.cpp -o CMakeFiles/nnp.dir/Controller.cpp.s

nnp/CMakeFiles/nnp.dir/Minesweeper.cpp.o: nnp/CMakeFiles/nnp.dir/flags.make
nnp/CMakeFiles/nnp.dir/Minesweeper.cpp.o: nnp/Minesweeper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hayden/dev/aieBootstrap/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object nnp/CMakeFiles/nnp.dir/Minesweeper.cpp.o"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nnp.dir/Minesweeper.cpp.o -c /home/hayden/dev/aieBootstrap/nnp/Minesweeper.cpp

nnp/CMakeFiles/nnp.dir/Minesweeper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nnp.dir/Minesweeper.cpp.i"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hayden/dev/aieBootstrap/nnp/Minesweeper.cpp > CMakeFiles/nnp.dir/Minesweeper.cpp.i

nnp/CMakeFiles/nnp.dir/Minesweeper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nnp.dir/Minesweeper.cpp.s"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hayden/dev/aieBootstrap/nnp/Minesweeper.cpp -o CMakeFiles/nnp.dir/Minesweeper.cpp.s

nnp/CMakeFiles/nnp.dir/MinesweeperController.cpp.o: nnp/CMakeFiles/nnp.dir/flags.make
nnp/CMakeFiles/nnp.dir/MinesweeperController.cpp.o: nnp/MinesweeperController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hayden/dev/aieBootstrap/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object nnp/CMakeFiles/nnp.dir/MinesweeperController.cpp.o"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nnp.dir/MinesweeperController.cpp.o -c /home/hayden/dev/aieBootstrap/nnp/MinesweeperController.cpp

nnp/CMakeFiles/nnp.dir/MinesweeperController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nnp.dir/MinesweeperController.cpp.i"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hayden/dev/aieBootstrap/nnp/MinesweeperController.cpp > CMakeFiles/nnp.dir/MinesweeperController.cpp.i

nnp/CMakeFiles/nnp.dir/MinesweeperController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nnp.dir/MinesweeperController.cpp.s"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hayden/dev/aieBootstrap/nnp/MinesweeperController.cpp -o CMakeFiles/nnp.dir/MinesweeperController.cpp.s

nnp/CMakeFiles/nnp.dir/NeuralNetwork.cpp.o: nnp/CMakeFiles/nnp.dir/flags.make
nnp/CMakeFiles/nnp.dir/NeuralNetwork.cpp.o: nnp/NeuralNetwork.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hayden/dev/aieBootstrap/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object nnp/CMakeFiles/nnp.dir/NeuralNetwork.cpp.o"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nnp.dir/NeuralNetwork.cpp.o -c /home/hayden/dev/aieBootstrap/nnp/NeuralNetwork.cpp

nnp/CMakeFiles/nnp.dir/NeuralNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nnp.dir/NeuralNetwork.cpp.i"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hayden/dev/aieBootstrap/nnp/NeuralNetwork.cpp > CMakeFiles/nnp.dir/NeuralNetwork.cpp.i

nnp/CMakeFiles/nnp.dir/NeuralNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nnp.dir/NeuralNetwork.cpp.s"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hayden/dev/aieBootstrap/nnp/NeuralNetwork.cpp -o CMakeFiles/nnp.dir/NeuralNetwork.cpp.s

nnp/CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.o: nnp/CMakeFiles/nnp.dir/flags.make
nnp/CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.o: nnp/NeuralNetworkProjectApp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hayden/dev/aieBootstrap/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object nnp/CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.o"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.o -c /home/hayden/dev/aieBootstrap/nnp/NeuralNetworkProjectApp.cpp

nnp/CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.i"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hayden/dev/aieBootstrap/nnp/NeuralNetworkProjectApp.cpp > CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.i

nnp/CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.s"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hayden/dev/aieBootstrap/nnp/NeuralNetworkProjectApp.cpp -o CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.s

nnp/CMakeFiles/nnp.dir/PatternRecognitionController.cpp.o: nnp/CMakeFiles/nnp.dir/flags.make
nnp/CMakeFiles/nnp.dir/PatternRecognitionController.cpp.o: nnp/PatternRecognitionController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hayden/dev/aieBootstrap/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object nnp/CMakeFiles/nnp.dir/PatternRecognitionController.cpp.o"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nnp.dir/PatternRecognitionController.cpp.o -c /home/hayden/dev/aieBootstrap/nnp/PatternRecognitionController.cpp

nnp/CMakeFiles/nnp.dir/PatternRecognitionController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nnp.dir/PatternRecognitionController.cpp.i"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hayden/dev/aieBootstrap/nnp/PatternRecognitionController.cpp > CMakeFiles/nnp.dir/PatternRecognitionController.cpp.i

nnp/CMakeFiles/nnp.dir/PatternRecognitionController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nnp.dir/PatternRecognitionController.cpp.s"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hayden/dev/aieBootstrap/nnp/PatternRecognitionController.cpp -o CMakeFiles/nnp.dir/PatternRecognitionController.cpp.s

nnp/CMakeFiles/nnp.dir/XORController.cpp.o: nnp/CMakeFiles/nnp.dir/flags.make
nnp/CMakeFiles/nnp.dir/XORController.cpp.o: nnp/XORController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hayden/dev/aieBootstrap/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object nnp/CMakeFiles/nnp.dir/XORController.cpp.o"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nnp.dir/XORController.cpp.o -c /home/hayden/dev/aieBootstrap/nnp/XORController.cpp

nnp/CMakeFiles/nnp.dir/XORController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nnp.dir/XORController.cpp.i"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hayden/dev/aieBootstrap/nnp/XORController.cpp > CMakeFiles/nnp.dir/XORController.cpp.i

nnp/CMakeFiles/nnp.dir/XORController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nnp.dir/XORController.cpp.s"
	cd /home/hayden/dev/aieBootstrap/nnp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hayden/dev/aieBootstrap/nnp/XORController.cpp -o CMakeFiles/nnp.dir/XORController.cpp.s

# Object files for target nnp
nnp_OBJECTS = \
"CMakeFiles/nnp.dir/main.cpp.o" \
"CMakeFiles/nnp.dir/Controller.cpp.o" \
"CMakeFiles/nnp.dir/Minesweeper.cpp.o" \
"CMakeFiles/nnp.dir/MinesweeperController.cpp.o" \
"CMakeFiles/nnp.dir/NeuralNetwork.cpp.o" \
"CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.o" \
"CMakeFiles/nnp.dir/PatternRecognitionController.cpp.o" \
"CMakeFiles/nnp.dir/XORController.cpp.o"

# External object files for target nnp
nnp_EXTERNAL_OBJECTS =

nnp/nnp: nnp/CMakeFiles/nnp.dir/main.cpp.o
nnp/nnp: nnp/CMakeFiles/nnp.dir/Controller.cpp.o
nnp/nnp: nnp/CMakeFiles/nnp.dir/Minesweeper.cpp.o
nnp/nnp: nnp/CMakeFiles/nnp.dir/MinesweeperController.cpp.o
nnp/nnp: nnp/CMakeFiles/nnp.dir/NeuralNetwork.cpp.o
nnp/nnp: nnp/CMakeFiles/nnp.dir/NeuralNetworkProjectApp.cpp.o
nnp/nnp: nnp/CMakeFiles/nnp.dir/PatternRecognitionController.cpp.o
nnp/nnp: nnp/CMakeFiles/nnp.dir/XORController.cpp.o
nnp/nnp: nnp/CMakeFiles/nnp.dir/build.make
nnp/nnp: bootstrap/libaieBootstrap.a
nnp/nnp: dependencies/glfw-source/src/libglfw3.a
nnp/nnp: /usr/lib/x86_64-linux-gnu/librt.so
nnp/nnp: /usr/lib/x86_64-linux-gnu/libm.so
nnp/nnp: /usr/lib/x86_64-linux-gnu/libX11.so
nnp/nnp: /usr/lib/x86_64-linux-gnu/libGL.so
nnp/nnp: nnp/CMakeFiles/nnp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hayden/dev/aieBootstrap/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable nnp"
	cd /home/hayden/dev/aieBootstrap/nnp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nnp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
nnp/CMakeFiles/nnp.dir/build: nnp/nnp

.PHONY : nnp/CMakeFiles/nnp.dir/build

nnp/CMakeFiles/nnp.dir/clean:
	cd /home/hayden/dev/aieBootstrap/nnp && $(CMAKE_COMMAND) -P CMakeFiles/nnp.dir/cmake_clean.cmake
.PHONY : nnp/CMakeFiles/nnp.dir/clean

nnp/CMakeFiles/nnp.dir/depend:
	cd /home/hayden/dev/aieBootstrap && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hayden/dev/aieBootstrap /home/hayden/dev/aieBootstrap/nnp /home/hayden/dev/aieBootstrap /home/hayden/dev/aieBootstrap/nnp /home/hayden/dev/aieBootstrap/nnp/CMakeFiles/nnp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : nnp/CMakeFiles/nnp.dir/depend

