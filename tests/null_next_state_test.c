#include <assert.h>

#include "fsm.h"

/**
 * @brief Test, that transition with null next are invalid
 * afterwards
 */

static int state1_call_count = 0;
static int state2_call_count = 0;

void hand1(void *ctx) {
    state1_call_count++;
}

void hand2(void *ctx) {
    state2_call_count++;
}

/* Events*/
DEFINE_EVENT(event1);

/* States */
DECLARE_STATE(state1);
/* Transitions */
DEFINE_STATE_TRANSITIONS(state1) = {
    TRANSITION(event1, NULL),
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
    assert(fsm_status == FSM_STATUS_INVALID_FSM);

    return 0;
}
