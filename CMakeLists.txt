cmake_minimum_required(VERSION 3.20)

project("Finite state machine framework"
        LANGUAGES C
        VERSION 1.0.0
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(BUILD_EXAMPLES "Build FSM examples" ON)
option(BUILD_TESTS "Build FSM tests" ON)

add_library(fsm)

target_sources(fsm PRIVATE src/fsm.c)
target_include_directories(fsm PUBLIC inc)

target_compile_options(fsm
  PRIVATE
  -Werror
  -Wall
  -Wextra
  -pedantic
  -Wpointer-arith
  -Wconversion
  -Wimplicit-fallthrough
  -Werror=implicit-function-declaration
  -Wno-sign-conversion
  -Wstrict-prototypes
  -Wmissing-prototypes
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()