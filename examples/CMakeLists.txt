add_executable(fsm_two_states_example two_states.c)

target_link_libraries(fsm_two_states_example PRIVATE fsm)

target_compile_options(fsm_two_states_example
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
