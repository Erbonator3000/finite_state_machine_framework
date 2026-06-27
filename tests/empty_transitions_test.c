#include <assert.h>

#include "fsm.h"

/**
 * @brief Test, taht empty transitions list causes the fsm to do nothing (but run first state once)
 */

static int state1_call_count = 0;

void hand1(void *ctx) {
    state1_call_count++;
}

/* States */
DECLARE_STATE(state1);

/* Transitions */
DEFINE_STATE_TRANSITIONS(state1) = {};

/* State declarations */
DEFINE_STATE(state1, hand1);

/* State machine construct */
FSM_STATES(state_machine1) = { state1 };
DEFINE_FSM(state_machine1, state1, NULL);

int main(void) {
    fsm_machine_status_t fsm_status;

    // Go to state1
    fsm_status = fsm_run(&state_machine1, NO_EVENT);
    assert(fsm_status == FSM_STATUS_OK);
    assert(state1_call_count == 1);

    // No transitions to do
    fsm_status = fsm_run(&state_machine1, NO_EVENT);
    assert(fsm_status == FSM_STATUS_OK);
    assert(state1_call_count == 1);

    return 0;
}
