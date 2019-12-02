set(MAIN_SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/gameworld.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/icon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ground.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ground_parse.cpp
  CACHE PATH "Main source files")

add_subdirectory(include)
add_subdirectory(exception)

add_executable(${EXECUTABLE_NAME}
  ${MAIN_SOURCE_FILES}
  ${MAIN_HEADER_FILES}
  )

target_include_directories(${EXECUTABLE_NAME}
  PRIVATE
  include
  exception)

target_link_libraries(${EXECUTABLE_NAME}
  PRIVATE
  sfml-graphics
  sfml-audio
  Threads::Threads
  m)

target_compile_definitions(${EXECUTABLE_NAME}
  PRIVATE VER_MAJOR=${PROJECT_VERSION_MAJOR}
  PRIVATE VER_MINOR=${PROJECT_VERSION_MINOR}
  PRIVATE VER_PATCH=${PROJECT_VERSION_PATCH}
  )

target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)
target_compile_options(${EXECUTABLE_NAME} PRIVATE $<$<CONFIG:DEBUG>:
  -Werror
  -g
  -Og
  -Wall
  -Wextra
  -Wshadow
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Wnull-dereference
  -Wdouble-promotion
  -Wformat=2
  -Wduplicated-cond
  -Wduplicated-branches
  -Wlogical-op
  -Wuseless-cast
  >)
