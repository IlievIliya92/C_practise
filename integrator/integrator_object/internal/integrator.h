#ifndef _INTEGRATOR_
#define _INTEGRATOR_

#include "integrator_object.h"

struct integrator {
	function f;
	double from;
	double to;
	double delta_x;
};
typedef struct integrator integrator;

#endif
