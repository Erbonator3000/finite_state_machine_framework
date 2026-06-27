#include <assert.h>

#include "fsm.h"

/**
 * @brief Test transitioning between states, verify that state handlers are called in right order and amount
 */

static int state1_call_count = 0;
static int state2_call_count = 0;

void hand(void *ctx) {
    state1_call_count++;
}

void hand2(void *ctx) {
    state2_call_count++;
}

/* Events*/
DEFINE_EVENT(event1);

/* States */
DECLARE_STATE(state1);
DECLARE_STATE(state2);

/* Transitions */
DEFINE_STATE_TRANSITIONS(state1) = {
    TRANSITION(event1, state2),
};
DEFINE_STATE_TRANSITIONS(state2) = {
    TRANSITION(event1, state1),
};

/* State declarations */
DEFINE_STATE(state1, hand);
DEFINE_STATE(state2, hand2);

/* State machine construct */
FSM_STATES(state_machine1) = { state1, state2 };
DEFINE_FSM(state_machine1, state1, NULL);

int main(void) {
    fsm_machine_status_t fsm_status;

    // Go to state1
    fsm_status = fsm_run(&state_machine1, NO_EVENT);
    assert(fsm_status == FSM_STATUS_OK);
    assert(state1_call_count == 1);
    assert(state2_call_count == 0);

    // Go to state2
    fsm_status = fsm_run(&state_machine1, event1);
    assert(fsm_status == FSM_STATUS_OK);
    assert(state1_call_count == 1);
    assert(state2_call_count == 1);

    return 0;
}
