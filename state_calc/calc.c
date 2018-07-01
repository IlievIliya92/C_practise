#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "calc.h"

int main(void) {
#if defined(HEX_CALC)
	do_hex_calc();
#elif defined(DEC_CALC)
	do_dec_calc();
#endif
	return 0;
}

