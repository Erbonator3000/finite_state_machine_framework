#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

typedef struct {
    bool triggered;
} event_t;

struct state_t;

struct transition_t {
    event_t *const event;
    const struct state_t *const next;
};

struct state_t {
    const struct transition_t *const transitions;
    size_t transition_count;
    void (*handler)(void);
};

struct fsm_t {
    const struct state_t *const states;
    const size_t state_count;
    const struct state_t *current_state;
};

/**
 * @def DEFINE_EVENT
 * @brief Create event object.
 *
 * @param event_name name of the event.
 */
#define DEFINE_EVENT(event_name) static event_t event_name = { .triggered = false }

/**
 * @def DECLARE_STATE
 * @brief Declare a fsm state (to be added to state transitions).
 *
 * @param name State name.
 *
 * @note All states must be defined before the transitions can be declared.
 */
#define DECLARE_STATE(name) static const struct state_t name

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
    { .event = &transition_event, .next = &transition_next }

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
    static const struct state_t name = { .handler = state_handler, \
                                         .transitions = name##_transitions, \
                                         .transition_count = sizeof(name##_transitions) \
                                           / sizeof(name##_transitions[0]) }

/**
 * @def FSM_STATES
 * @brief Defines a list of states in the state machine
 *
 * @param name Name of the fsm for which the state table is defined.
 */
#define FSM_STATES(name) static const struct state_t name##_states[]

/**
 * @def DEFINE_FSM
 * @brief Define a fsm object.
 *
 * @param name Name of the fsm to create.
 */
#define DEFINE_FSM(name) \
    static_assert(sizeof(name##_states) > 0, "Empty state machines not allowed"); \
    static struct fsm_t name = { .states = name##_states, \
                                 .state_count = sizeof(name##_states) / sizeof(name##_states[0]), \
                                 .current_state = &name##_states[0] }

typedef enum {
    FSM_STATUS_OK,
    FSM_STATUS_INVALID_FSM,
    FSM_STATUS_INVALID_STATE,
} fsm_machine_status_t;

void trigger_event(event_t *event_name);
fsm_machine_status_t fsm_run(struct fsm_t *const fsm);
