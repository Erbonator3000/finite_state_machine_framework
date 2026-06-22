#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "fsm.h"

void hand(void) {
    printf("Handling1...\n");
}

void hand2(void) {
    printf("Handling2...\n");
}

/* Events*/
DEFINE_EVENT(event1);
// DEFINE_EVENT(event2);

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
FSM_STATES(foo) = { state1, state2 };
DEFINE_FSM(foo);

int main(void) {
    fsm_machine_status_t fsm_status;
    while (true) {
        trigger_event(&event1);
        fsm_status = fsm_run(&foo);
        if (fsm_status != FSM_STATUS_OK) {
            printf("FSM failed");
            break;
        }
    }
    return 0;
}
