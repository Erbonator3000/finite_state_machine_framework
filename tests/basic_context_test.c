#include <assert.h>

#include "fsm.h"

/**
 * @brief Test, that transition to self state stays in current state and executes handler, and can transit in to other
 * states afterwards
 */

static int call_count1 = 0;
static int call_count2 = 0;

void hand(void *ctx) {
    int *counter = (int *) ctx;
    (*counter)++;
}

/* Events*/
DEFINE_EVENT(event1);

/* States */
DECLARE_STATE(state1);

/* Transitions */
DEFINE_STATE_TRANSITIONS(state1) = {};

/* State declarations */
DEFINE_STATE(state1, hand);

/* State machine construct */
FSM_STATES(state_machine1) = { state1 };
DEFINE_FSM(state_machine1, state1, (void *) &call_count1);

FSM_STATES(state_machine2) = { state1 };
DEFINE_FSM(state_machine2, state1, (void *) &call_count2);

int main(void) {
    fsm_machine_status_t fsm_status;

    // State machine 1 go to state1
    fsm_status = fsm_run(&state_machine1, NO_EVENT);
    assert(fsm_status == FSM_STATUS_OK);
    assert(call_count1 == 1);
    assert(call_count2 == 0);

    // State machine 2 go to state1
    fsm_status = fsm_run(&state_machine2, event1);
    assert(fsm_status == FSM_STATUS_OK);
    assert(call_count1 == 1);
    assert(call_count2 == 1);

    return 0;
}
