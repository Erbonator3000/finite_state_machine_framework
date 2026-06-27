#include <assert.h>

#include "fsm.h"

/**
 * @brief Test, that null transition list causes failure on fsm and return error code
 */

static int state1_call_count = 0;

void hand(void *ctx) {
    state1_call_count++;
}

/* States */
DECLARE_STATE(state1);

/* State declarations */
// For this test manually created state object is needed (null transition pointer will compile error)
static const struct state_t state1_object = { .handler = hand, .transitions = NULL, .transition_count = 0 };

/* State machine construct */
FSM_STATES(state_machine1) = { state1 };
DEFINE_FSM(state_machine1, state1, NULL);

int main(void) {
    fsm_machine_status_t fsm_status;

    // Null transitions list caught on first run, before running initial state handler
    fsm_status = fsm_run(&state_machine1, NO_EVENT);
    assert(fsm_status == FSM_STATUS_INVALID_FSM);
    assert(state1_call_count == 0);

    return 0;
}
