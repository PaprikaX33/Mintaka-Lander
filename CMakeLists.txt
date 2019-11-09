cmake_minimum_required(VERSION 3.13)
project(MintakaLander VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

add_custom_target(link_font ALL
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/font ${CMAKE_BINARY_DIR}/font)

set(EXECUTABLE_NAME ${PROJECT_NAME}
  CACHE STRING "Executable's name")

find_package(Threads REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_subdirectory(src)
