#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "fsmlt.h"


#define MAXTIMEOUT 		20

static int timeout = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static bool enable_start = false;

void delay(int number_of_seconds);
void *start_handler(void *ptr);
void *stop_handler(void *ptr);
pthread_t startcp, stopcp;


void usage_fsm (void)
{
	fprintf(stdout, "State allowed sequences 0 -> 1 -> 2 \n");
	fprintf(stdout, " 			|-------- | \n");
	exit(1);
}

//Prototype of eventhandlers
eSystemState init_handler(void)
{
    printf("Initialized;\n");
    return Data_State;
}

eSystemState data_handler(void)
{
    int rs;
    enable_start = true;

    printf("Collect data;\n");

    // start the threads
    rs = pthread_create(&startcp, NULL, *start_handler, NULL);
    if (rs != 0)
    {
    	fprintf(stderr, "Failed to create StartCP\n");
    }
    else
    {
    	fprintf(stdout, "StartCP thread created!\n");
    }

    rs = pthread_create(&stopcp, NULL, *stop_handler, NULL);
	if (rs != 0)
    {
    	fprintf(stderr, "Failed to create StopCP\n");
    }
    else
    {
    	fprintf(stdout, "StopCp thread created!\n");
    }

    return Reset_State;
}

eSystemState reset_handler(void)
{
    printf("Reset state;\n");

    return Idle_State;
}

eSystemState error_handler (void)
{
	exit(1);
	return Error_State;
}

eSystemEvent read_event (void)
{
    eSystemEvent event;
    int user_in = 0;

    printf("User input: ");
    scanf("%d", &user_in);

    switch (user_in)
    {
        case 0:
	        event = Detect_Trigger;
	        break;
	    case 1:
	        event = Data_Event;
	        break;
	    case 2:
	        event = Reset_Event;
	        break;

	    default:
	    	event = Error_Event;
			usage_fsm();
	        break;
	}

    return event;
}


void *start_handler(void *ptr)
{
	while (1)
	{
		if (enable_start)
		{
		   	fprintf(stdout, "running!\n");
		   	delay(10);
		   	timeout++;
		}
	}

	return NULL;
}

void *stop_handler(void *ptr)
{
	while (1)
	{
		if (timeout > MAXTIMEOUT)
		{
			enable_start = false;
			timeout = 0;
			fprintf(stdout, "stopped!\n");
			fprintf(stdout, "Press 2 to reset!\n");
			pthread_join(startcp,NULL);
			pthread_join(stopcp,NULL);
		}

	}

	return NULL;
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}
