/* Copyright (c) 2026 Eero Prittinen, SPDX-License-Identifier: MIT */

#ifndef FSM_H
#define FSM_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

typedef uint32_t event_t;

struct state_t;

struct transition_t {
    const event_t event;
    const struct state_t *const next;
};

struct state_t {
    const struct transition_t *const transitions;
    const size_t transition_count;
    void (*const handler)(void *ctx);
};

struct fsm_t {
    const struct state_t *const *const states;
    const size_t state_count;
    const struct state_t *current_state;
    const struct state_t *const initial_state;
    bool running;
    void *ctx;
};

/**
 * @def NO_EVENT
 * @brief Create event constant for no event.
 */
#define NO_EVENT ((uint32_t) __COUNTER__)

/**
 * @def DEFINE_EVENT
 * @brief Create event constant.
 *
 * @param event_name name of the event.
 */
#define DEFINE_EVENT(name) static const event_t name = __COUNTER__

/**
 * @def DECLARE_STATE
 * @brief Declare a fsm state pointer (to be added to state transitions).
 *
 * @param name State name.
 *
 * @note All states must be defined before the transitions can be declared.
 */
#define DECLARE_STATE(name) \
    static const struct state_t const name##_object; \
    static const struct state_t *const name = &name##_object

/**
 * @def TRANSITION
 * @brief Define a sinfle fsm transition.
 *
 * @param transition_event Event to trigger the state transition.
 *
 * @param transition_next State to transition to.
 *
 * @note All states must be defined before the transitions can be declared.
 */
#define TRANSITION(transition_event, transition_next) \
    { .event = transition_event, .next = transition_next }

/**
 * @def DEFINE_STATE_TRANSITIONS
 * @brief Declares a static transition table for a state in a state machine.
 *
 * @note Intended to be used together with TRANSITION() entries.
 *
 * @code
 * DEFINE_STATE_TRANSITIONS(state_1) = {
 *     TRANSITION(event_1, state_2),
 *     TRANSITION(event_2, state_3),
 * };
 * @endcode
 *
 * @note Events priority is order on the transition list
 *
 * @param name Name of the state for which the transition table is defined.
 */
#define DEFINE_STATE_TRANSITIONS(name) static const struct transition_t name##_transitions[]

#define DEFINE_STATE(name, state_handler) \
    static const struct state_t name##_object = { .handler = state_handler, \
                                                  .transitions = name##_transitions, \
                                                  .transition_count = sizeof(name##_transitions) \
                                                    / sizeof(name##_transitions[0]) }

/**
 * @def FSM_STATES
 * @brief Defines a list of states in the state machine
 *
 * @param name Name of the fsm for which the state table is defined.
 */
#define FSM_STATES(name) static const struct state_t *const name##_states[]

/**
 * @def DEFINE_FSM
 * @brief Define a fsm object.
 *
 * @param name Name of the fsm to create.
 * @param init_state Initial state of the state machine. The initial state handler will be executed once before checking
 * for transition event.
 * @param context The context pointer passed to the state machine handlers.
 */
#define DEFINE_FSM(name, init_state, context) \
    _Static_assert(sizeof(name##_states) > 0, "Empty state machines not allowed"); \
    static struct fsm_t name = { \
        .states = name##_states, \
        .state_count = sizeof(name##_states) / sizeof(name##_states[0]), \
        .current_state = init_state, \
        .initial_state = init_state, \
        .running = false, \
        .ctx = context, \
    }

typedef enum {
    FSM_STATUS_OK,
    FSM_STATUS_INVALID_FSM,
    FSM_STATUS_INVALID_STATE,
} fsm_machine_status_t;

fsm_machine_status_t fsm_run(struct fsm_t *const fsm, const event_t event);

#endif /* FSM_H */
