#ifndef _CALC_
#define _CALC_

struct callback_ctx {
	void *stack;
	int symbol;
	int accumulator;
	int negate;
};
typedef struct callback_ctx callback_ctx;

void do_dec_calc(void);
void do_hex_calc(void);

#endif
