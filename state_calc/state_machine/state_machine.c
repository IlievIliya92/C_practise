#include "state_machine.h"

void init_state_machine(state_machine *ctx, int start, event_table *events, void *callback_ctx) {
	ctx->current = start;
	ctx->events = events;
	ctx->callback_ctx = callback_ctx;
	return;
}

int run_state_machine(state_machine *ctx, int event) {
	int j, r = 0;
	
	for (j = 0; ctx->events[j].cur_state != EOET; j++)
		if ((ctx->events[j].cur_state == ctx->current) && (ctx->events[j].event == event)) {
			if (ctx->events[j].callback)
				r = ctx->events[j].callback(ctx->callback_ctx, ctx->events[j].cur_state, event, ctx->events[j].next_state);
			else r = 1;
			if (r) ctx->current = ctx->events[j].next_state;
			break;
		}
	
	return r;
}

