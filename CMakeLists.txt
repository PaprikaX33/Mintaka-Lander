cmake_minimum_required(VERSION 3.13)
project(MintakaLander VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#add_compile_definitions(
#  VER_MAJOR=${PROJECT_VERSION_MAJOR}
#  VER_MINOR=${PROJECT_VERSION_MINOR}
#  VER_PATCH=${PROJECT_VERSION_PATCH}
#  )


## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

set(EXECUTABLE_NAME ${PROJECT_NAME}
  CACHE STRING "Executable's name")

find_package(Threads REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_subdirectory(src)
