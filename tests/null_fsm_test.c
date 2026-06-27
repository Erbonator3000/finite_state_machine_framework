#include <assert.h>

#include "fsm.h"

/**
 * @brief Test, that null fsm pointer fails with error code
 */

int main(void) {
    fsm_machine_status_t fsm_status;

    fsm_status = fsm_run(NULL, NO_EVENT);
    assert(fsm_status == FSM_STATUS_INVALID_FSM);

    return 0;
}
