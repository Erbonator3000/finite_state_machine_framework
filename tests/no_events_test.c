#include <assert.h>

#include "fsm.h"

/**
 * @brief Test, that if no events are fired, fsm does nothing afer initial state run
 */

static int state1_call_count = 0;

void hand1(void *ctx) {
    state1_call_count++;
}

/* Events*/
DEFINE_EVENT(event1);

/* States */
DECLARE_STATE(state1);

/* Transitions */
DEFINE_STATE_TRANSITIONS(state1) = {
    TRANSITION(event1, state1),
};

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

    // Nothing should happen
    fsm_status = fsm_run(&state_machine1, NO_EVENT);
    assert(fsm_status == FSM_STATUS_OK);
    assert(state1_call_count == 1);

    return 0;
}
