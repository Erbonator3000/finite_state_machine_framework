#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h> // For sleep
#include "fsm.h"

static void hand(void *ctx) {
    (void) ctx;
    printf("Handling1...\n");
}

static void hand2(void *ctx) {
    (void) ctx;
    printf("Handling2...\n");
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
DEFINE_FSM(state_machine1, state2, NULL);

int main(void) {
    fsm_machine_status_t fsm_status;
    while (true) {
        fsm_status = fsm_run(&state_machine1, event1);
        if (fsm_status != FSM_STATUS_OK) {
            printf("FSM failed");
            break;
        }

        sleep(1);
    }
    return 0;
}
