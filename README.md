# Finite State Machine
This is a refernce implementation for lightweight finite state machine implementation for c and embedded c applications.

The main design drivers:
- Static construction: Build time construction of fsm to minimize runtime overhead and errors
- Portability: Minimum platform dependency, single header file library
- Simplicity: Only does state transition resolving
- Constraining: Defines one allowed approach to create states, events and transitions

**NOTE: This framework is still in development, API might change unannounced**

## Usage

### Events
Events are defined using `DEFINE_EVENT` macro.
```C
DEFINE_EVENT(event1);
```
This creates unique event constant named `event1`.

**NOTE: Events are static scoped, so defining an event with the same name on another file does not correspond to the same fsm event.

### States and transitions
All states must be declared before they can be defined, as declarations of states are used to define the transitions (which are then used in the definitions of the states). State is declared using `DECLARE_STATE` macro.
```c
DECLARE_STATE(state1);
```

Transitions are defined for each state using `DEFINE_STATE_TRANSITIONS` macro. Transition definition should equal to a list of Transition objects, that are created with `TRANSITION` macro. `TRANSITION` macro takes as a parameter the event which would cause the transition and the state name to which transition to.
```c
DEFINE_STATE_TRANSITIONS(state1) = {
    TRANSITION(event1, state2),
};
```

After transitions are defined, the tates can be defined by calling `DEFINE_STATE` macro. `DEFINE_STATE` macro takse the state name as a parameter, as well as the handler function, which should be of signature `void (*handler)(void)`.
```c
DEFINE_STATE(state1, handler);
```

### State machine creation
To allow evaluation of the state machine correctness, create an allowed states list using `FSM_STATES` macro, giving the name of the statemachine as a parameter.
```c
FSM_STATES(state_machine1) = { state1, state2 };
```

Finally define the state machine entity with `DEFINE_FSM` macro. Parameters are the state machine name, the first state to go to, and the context pointer passed to the state handler functions.
```c
DEFINE_FSM(state_machine1, state2, context);
```

**NOTE: The underlaying design allows for multiple statemachine objects to be defined with the same states, as staest, transitions, and events are only immuteable descriptions and do not hold state**

### Stepping trough states
The statemachine is run by calling the `fsm_run` function, supplying the statemachine object and the event. `fsm_run` returns the state machine status.
```c
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
```

### First run behaviour
As this state machine does not have separate `start` or `init` runtime procedure, the running of the first state is handled as part of the `fsm_run` function. The initial state handler (if not `NULL`) is always run on the first call of the `fsm_run` as if that state was just enered trough transition following an event. If the first run is supplied an event (not `NO_EVENT`), that event is evaluated after the initial state handler is run (if not `NULL`), and if transition is derived from the event, the state machine will transition to that new state and execute it's handler as well.

To prevent the "Double handler" run in the first `fsm_run` call, the `event` parameter can be omitted by using `NO_EVENT`, in which case only the initial state handler is executed (if not `NULL`).

## License
See `LICENSE` file.
