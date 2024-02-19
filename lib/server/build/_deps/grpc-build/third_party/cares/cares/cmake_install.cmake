# Install script for directory: /Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-src/third_party/cares/cares

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares/c-ares-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares/c-ares-targets.cmake"
         "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build/third_party/cares/cares/CMakeFiles/Export/e1b1c4e2e08fd55c0020938b7b6a2645/c-ares-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares/c-ares-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares/c-ares-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares" TYPE FILE FILES "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build/third_party/cares/cares/CMakeFiles/Export/e1b1c4e2e08fd55c0020938b7b6a2645/c-ares-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares" TYPE FILE FILES "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build/third_party/cares/cares/CMakeFiles/Export/e1b1c4e2e08fd55c0020938b7b6a2645/c-ares-targets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/c-ares" TYPE FILE FILES
    "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build/third_party/cares/cares/c-ares-config.cmake"
    "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build/third_party/cares/cares/c-ares-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build/third_party/cares/cares/libcares.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build/third_party/cares/cares/include/cmake_install.cmake")
  include("/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build/third_party/cares/cares/src/cmake_install.cmake")
  include("/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build/third_party/cares/cares/docs/cmake_install.cmake")

endif()

