#ifndef _STATE_MACHINE_
#define _STATE_MACHINE_

enum {
	EOET = -1
};

typedef int (*action_callback)(void *ctx, int cur_state, int event, int next_state);

struct event_table {
	int cur_state;
	int event;
	int next_state;
	action_callback callback;
};
typedef struct event_table event_table;

struct state_machine {
	int current;
	event_table *events;
	void *callback_ctx;
};
typedef struct state_machine state_machine;

void init_state_machine(state_machine *ctx, int start, event_table *events, void *callback_ctx);
int run_state_machine(state_machine *ctx, int event);

#endif
