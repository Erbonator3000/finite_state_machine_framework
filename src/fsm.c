/* Copyright (c) 2026 Eero Prittinen, SPDX-License-Identifier: MIT */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "fsm.h"

static bool fsm_validate(const struct fsm_t *const fsm) {
    // Check trough all state transitions and check that all states are within this state machine
    // Check initial state also
    bool initial_state_ok = false;
    for (size_t i = 0; i < fsm->state_count; i++) {
        // Check initial state
        if (fsm->states[i] == fsm->initial_state) {
            initial_state_ok = true;
        }

        if (fsm->states[i]->transitions == NULL) {
            return false;
        }

        for (size_t j = 0; j < fsm->states[i]->transition_count; j++) {
            // Check for invalid value
            if (fsm->states[i]->transitions[j].next == NULL) {
                return false;
            }

            // Check for transition contained in thsi state machine
            bool transition_ok = false;
            for (size_t k = 0; k < fsm->state_count; k++) {
                if (fsm->states[i]->transitions[j].next == fsm->states[k]) {
                    transition_ok = true;
                    break;
                }
            }
            if (!transition_ok) {
                return false;
            }
        }
    }
    return initial_state_ok;
}

/**
 * @brief Runs one iteration of state machine
 * @param fsm Finite state machine to operate on
 * @param event Event triggered and fed to the fsm
 * @retval FSM_STATUS_OK Success
 * @retval FSM_STATUS_INVALID_FSM Invalid fsm
 * @retval FSM_STATUS_INVALID_STATE Invalid state
 */
fsm_machine_status_t fsm_run(struct fsm_t *const fsm, const event_t event) {
    const struct transition_t *next_transition = NULL;
    if (fsm == NULL) {
        return FSM_STATUS_INVALID_FSM;
    }

    // Special handling for the initial state
    if (!fsm->running) {
        // Validate fsm once on start
        if (!fsm_validate(fsm)) {
            return FSM_STATUS_INVALID_FSM;
        }

        fsm->current_state = fsm->initial_state;
        fsm->running = true;
        if (fsm->current_state->handler != NULL) {
            fsm->current_state->handler(fsm->ctx);
        }
        // Continue to normal operation to evaluate event, (if supplied)
    }

    if (fsm->current_state == NULL) {
        return FSM_STATUS_INVALID_STATE;
    }

    // All states transition lists are checked to be not NULL in fsm_validate
    for (size_t i = 0; i < fsm->current_state->transition_count; i++) {
        if (fsm->current_state->transitions[i].event == event) {
            next_transition = &fsm->current_state->transitions[i];
            break;
        }
    }

    // No next tranistion -> go back to waiting events
    if (next_transition == NULL) {
        return FSM_STATUS_OK;
    }

    // next_transition->next != NULL Checked already in fsm_validate
    fsm->current_state = next_transition->next;

    if (fsm->current_state->handler != NULL) {
        fsm->current_state->handler(fsm->ctx);
    }
    return FSM_STATUS_OK;
}
