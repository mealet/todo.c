# Project Definition and Flags

cmake_minimum_required(VERSION 3.21)
project(todo C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap")

# Executable

add_executable(
  ${PROJECT_NAME}
  src/main.c
)

# Libraries

add_subdirectory(src/object)
add_subdirectory(src/storage)
add_subdirectory(src/utils)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  object storage utils
)
