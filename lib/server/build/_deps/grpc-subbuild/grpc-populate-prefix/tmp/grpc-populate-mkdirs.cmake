# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-src"
  "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-build"
  "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-subbuild/grpc-populate-prefix"
  "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-subbuild/grpc-populate-prefix/tmp"
  "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-subbuild/grpc-populate-prefix/src/grpc-populate-stamp"
  "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-subbuild/grpc-populate-prefix/src"
  "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-subbuild/grpc-populate-prefix/src/grpc-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-subbuild/grpc-populate-prefix/src/grpc-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/gautamsharma/CS/C++/redislite/lib/server/build/_deps/grpc-subbuild/grpc-populate-prefix/src/grpc-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
