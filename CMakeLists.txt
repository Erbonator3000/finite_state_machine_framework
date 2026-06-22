cmake_minimum_required(VERSION 3.20)

project(fsm_lib)

add_executable(main)

target_sources(main PRIVATE src/main.c src/fsm.c)
target_include_directories(main PRIVATE inc)

target_compile_options(main
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
)
