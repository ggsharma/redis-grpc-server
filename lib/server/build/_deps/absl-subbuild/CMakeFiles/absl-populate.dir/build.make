# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild

# Utility rule file for absl-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/absl-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/absl-populate.dir/progress.make

CMakeFiles/absl-populate: CMakeFiles/absl-populate-complete

CMakeFiles/absl-populate-complete: absl-populate-prefix/src/absl-populate-stamp/absl-populate-install
CMakeFiles/absl-populate-complete: absl-populate-prefix/src/absl-populate-stamp/absl-populate-mkdir
CMakeFiles/absl-populate-complete: absl-populate-prefix/src/absl-populate-stamp/absl-populate-download
CMakeFiles/absl-populate-complete: absl-populate-prefix/src/absl-populate-stamp/absl-populate-update
CMakeFiles/absl-populate-complete: absl-populate-prefix/src/absl-populate-stamp/absl-populate-patch
CMakeFiles/absl-populate-complete: absl-populate-prefix/src/absl-populate-stamp/absl-populate-configure
CMakeFiles/absl-populate-complete: absl-populate-prefix/src/absl-populate-stamp/absl-populate-build
CMakeFiles/absl-populate-complete: absl-populate-prefix/src/absl-populate-stamp/absl-populate-install
CMakeFiles/absl-populate-complete: absl-populate-prefix/src/absl-populate-stamp/absl-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'absl-populate'"
	/opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E make_directory /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles
	/opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E touch /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles/absl-populate-complete
	/opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E touch /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/src/absl-populate-stamp/absl-populate-done

absl-populate-prefix/src/absl-populate-stamp/absl-populate-update:
.PHONY : absl-populate-prefix/src/absl-populate-stamp/absl-populate-update

absl-populate-prefix/src/absl-populate-stamp/absl-populate-build: absl-populate-prefix/src/absl-populate-stamp/absl-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'absl-populate'"
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-build && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E echo_append
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-build && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E touch /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/src/absl-populate-stamp/absl-populate-build

absl-populate-prefix/src/absl-populate-stamp/absl-populate-configure: absl-populate-prefix/tmp/absl-populate-cfgcmd.txt
absl-populate-prefix/src/absl-populate-stamp/absl-populate-configure: absl-populate-prefix/src/absl-populate-stamp/absl-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'absl-populate'"
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-build && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E echo_append
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-build && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E touch /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/src/absl-populate-stamp/absl-populate-configure

absl-populate-prefix/src/absl-populate-stamp/absl-populate-download: absl-populate-prefix/src/absl-populate-stamp/absl-populate-gitinfo.txt
absl-populate-prefix/src/absl-populate-stamp/absl-populate-download: absl-populate-prefix/src/absl-populate-stamp/absl-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'absl-populate'"
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -P /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/tmp/absl-populate-gitclone.cmake
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E touch /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/src/absl-populate-stamp/absl-populate-download

absl-populate-prefix/src/absl-populate-stamp/absl-populate-install: absl-populate-prefix/src/absl-populate-stamp/absl-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'absl-populate'"
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-build && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E echo_append
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-build && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E touch /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/src/absl-populate-stamp/absl-populate-install

absl-populate-prefix/src/absl-populate-stamp/absl-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'absl-populate'"
	/opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -Dcfgdir= -P /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/tmp/absl-populate-mkdirs.cmake
	/opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E touch /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/src/absl-populate-stamp/absl-populate-mkdir

absl-populate-prefix/src/absl-populate-stamp/absl-populate-patch: absl-populate-prefix/src/absl-populate-stamp/absl-populate-patch-info.txt
absl-populate-prefix/src/absl-populate-stamp/absl-populate-patch: absl-populate-prefix/src/absl-populate-stamp/absl-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'absl-populate'"
	/opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E echo_append
	/opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E touch /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/src/absl-populate-stamp/absl-populate-patch

absl-populate-prefix/src/absl-populate-stamp/absl-populate-update:
.PHONY : absl-populate-prefix/src/absl-populate-stamp/absl-populate-update

absl-populate-prefix/src/absl-populate-stamp/absl-populate-test: absl-populate-prefix/src/absl-populate-stamp/absl-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'absl-populate'"
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-build && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E echo_append
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-build && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E touch /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/src/absl-populate-stamp/absl-populate-test

absl-populate-prefix/src/absl-populate-stamp/absl-populate-update: absl-populate-prefix/tmp/absl-populate-gitupdate.cmake
absl-populate-prefix/src/absl-populate-stamp/absl-populate-update: absl-populate-prefix/src/absl-populate-stamp/absl-populate-update-info.txt
absl-populate-prefix/src/absl-populate-stamp/absl-populate-update: absl-populate-prefix/src/absl-populate-stamp/absl-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'absl-populate'"
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-src && /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -Dcan_fetch=YES -P /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/absl-populate-prefix/tmp/absl-populate-gitupdate.cmake

absl-populate: CMakeFiles/absl-populate
absl-populate: CMakeFiles/absl-populate-complete
absl-populate: absl-populate-prefix/src/absl-populate-stamp/absl-populate-build
absl-populate: absl-populate-prefix/src/absl-populate-stamp/absl-populate-configure
absl-populate: absl-populate-prefix/src/absl-populate-stamp/absl-populate-download
absl-populate: absl-populate-prefix/src/absl-populate-stamp/absl-populate-install
absl-populate: absl-populate-prefix/src/absl-populate-stamp/absl-populate-mkdir
absl-populate: absl-populate-prefix/src/absl-populate-stamp/absl-populate-patch
absl-populate: absl-populate-prefix/src/absl-populate-stamp/absl-populate-test
absl-populate: absl-populate-prefix/src/absl-populate-stamp/absl-populate-update
absl-populate: CMakeFiles/absl-populate.dir/build.make
.PHONY : absl-populate

# Rule to build all files generated by this target.
CMakeFiles/absl-populate.dir/build: absl-populate
.PHONY : CMakeFiles/absl-populate.dir/build

CMakeFiles/absl-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/absl-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/absl-populate.dir/clean

CMakeFiles/absl-populate.dir/depend:
	cd /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/absl-subbuild/CMakeFiles/absl-populate.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/absl-populate.dir/depend
