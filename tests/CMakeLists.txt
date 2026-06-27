cmake_minimum_required(VERSION 3.20)

project(fsm_tests C)

enable_testing()

# Basic state transition test
add_executable(basic_state_transition_test
    basic_state_transition_test.c
)

target_link_libraries(basic_state_transition_test PRIVATE fsm)

add_test(
    NAME basic_state_transition_test
    COMMAND basic_state_transition_test
)

# Immidiate event test
add_executable(immediate_event_test
    immediate_event_test.c
)

target_link_libraries(immediate_event_test PRIVATE fsm)

add_test(
    NAME immediate_event_test
    COMMAND immediate_event_test
)

# NULL handler test
add_executable(null_handler_test
    null_handler_test.c
)

target_link_libraries(null_handler_test PRIVATE fsm)

add_test(
    NAME null_handler_test
    COMMAND null_handler_test
)

# NULL next state test
add_executable(null_next_state_test
    null_next_state_test.c
)

target_link_libraries(null_next_state_test PRIVATE fsm)

add_test(
    NAME null_next_state_test
    COMMAND null_next_state_test
)

# Self transition test
add_executable(self_transition_test
    self_transition_test.c
)

target_link_libraries(self_transition_test PRIVATE fsm)

add_test(
    NAME self_transition_test
    COMMAND self_transition_test
)

# NULL fsm test
add_executable(null_fsm_test
    null_fsm_test.c
)

target_link_libraries(null_fsm_test PRIVATE fsm)

add_test(
    NAME null_fsm_test
    COMMAND null_fsm_test
)


# NULL transitions test
add_executable(null_transitions_test
    null_transitions_test.c
)

target_link_libraries(null_transitions_test PRIVATE fsm)

add_test(
    NAME null_transitions_test
    COMMAND null_transitions_test
)

# Empty transitions test
add_executable(empty_transitions_test
    empty_transitions_test.c
)

target_link_libraries(empty_transitions_test PRIVATE fsm)

add_test(
    NAME empty_transitions_test
    COMMAND empty_transitions_test
)

# No events test
add_executable(no_events_test
    no_events_test.c
)

target_link_libraries(no_events_test PRIVATE fsm)

add_test(
    NAME no_events_test
    COMMAND no_events_test
)

# Outside state test
add_executable(outside_state_test
    outside_state_test.c
)

target_link_libraries(outside_state_test PRIVATE fsm)

add_test(
    NAME outside_state_test
    COMMAND outside_state_test
)

# Basic context test
add_executable(basic_context_test
    basic_context_test.c
)

target_link_libraries(basic_context_test PRIVATE fsm)

add_test(
    NAME basic_context_test
    COMMAND basic_context_test
)
