#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "fsmlt.h"

//Initialize array of structure with states and event with proper handler
sStateMachine asStateMachine [] = {
	{Idle_State,Detect_Trigger,init_handler},
	{Data_State,Data_Event,data_handler},
	{Reset_State,Reset_Event,reset_handler},

};

//main function
int main(int argc, char *argv[]) {


    /* Initializa the fsm to Idle_State */
	eSystemState eNextState = Idle_State;
	while(1)
	{
		//Api read the event
		eSystemEvent eNewEvent = read_event();

		if((eNextState < last_State) && (eNewEvent < last_Event)&& (asStateMachine[eNextState].eStateMachineEvent == eNewEvent) && (asStateMachine[eNextState].pfStateMachineEvnentHandler != NULL))
		{
		// function call as per the state and event and return the next state of the finite state machine
			eNextState = (*asStateMachine[eNextState].pfStateMachineEvnentHandler)();
		}
		else
		{
			usage_fsm();
		}

	}

	return 0;
}
