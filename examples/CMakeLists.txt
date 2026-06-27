add_executable(fsm_two_states_example two_states.c)

target_link_libraries(fsm_two_states_example PRIVATE fsm)

target_include_directories(fsm_two_states_example PRIVATE ${CMAKE_SOURCE_DIR}/include)