#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "fsm.h"

/**
 * @brief Marks event as triggered
 * @param event
 */
void trigger_event(event_t *event) {
    event->triggered = true;
}

/**
 * @brief Runs one iteration of state machine
 * @param fsm Finite state machine to operate on
 * @return FSM_STATUS_OK on success, FSM_STATUS_INVALID_FSM on invalid fsm, or FSM_STATUS_INVALID_STATE on invalid state
 */
fsm_machine_status_t fsm_run(struct fsm_t *const fsm) {
    const struct transition_t *next_transition = NULL;
    if (fsm == NULL) {
        return FSM_STATUS_INVALID_FSM;
    }

    if (fsm->current_state == NULL) {
        return FSM_STATUS_INVALID_STATE;
    }

    if (fsm->current_state->transitions == NULL) {
        return FSM_STATUS_INVALID_FSM;
    }

    for (size_t i = 0; i < fsm->current_state->transition_count; i++) {
        if (fsm->current_state->transitions[i].event->triggered == true) {
            next_transition = &fsm->current_state->transitions[i];
            break;
        }
    }
    // No next tranistion -> go back to waiting events
    if (next_transition == NULL) {
        return FSM_STATUS_OK;
    }

    // Clear event
    next_transition->event->triggered = false;

    if (next_transition->next != NULL) {
        fsm->current_state = next_transition->next;
    }
    // If event defined but no next state -> redo current state

    if (fsm->current_state->handler != NULL) {
        fsm->current_state->handler();
    }
    return FSM_STATUS_OK;
}
