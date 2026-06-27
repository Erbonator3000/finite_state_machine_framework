#include <assert.h>

#include "fsm.h"

/**
 * @brief Test, that state transition to state outside of the statemachine allowed states is not possible
 */

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
    TRANSITION(event1, state2),
};

/* State declarations */
DEFINE_STATE(state1, NULL);
DEFINE_STATE(state2, NULL);

/* State machine construct */
FSM_STATES(state_machine1) = { state1 };
DEFINE_FSM(state_machine1, state1, NULL);

int main(void) {
    fsm_machine_status_t fsm_status;

    // State machine is invalid, as it has transition outside of the allowed states list
    fsm_status = fsm_run(&state_machine1, NO_EVENT);
    assert(fsm_status == FSM_STATUS_INVALID_FSM);
}
