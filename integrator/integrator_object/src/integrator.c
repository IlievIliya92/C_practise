#include <stdlib.h>

#include "integrator_object.h"
#include "internal/integrator.h"

void *integrator_create(double from, double to, double delta_x, function f) {
	integrator *i = (integrator *)malloc(sizeof (integrator));
	
	if (!i) return NULL;
	
	i->from = from;
	i->to = to;
	i->delta_x = delta_x;
	i->f = f;
	
	return (void *)i;
}

void integrator_destroy(void *_integrator) {
	free(_integrator);
	return;
}

double integrate(void *_integrator) {
	integrator *i = (integrator *)_integrator;
	double x, prev_y, y;
	double integral;
	
	prev_y = 0.0;
	integral = 0.0;
	
	for (x = i->from; x < i->to; x += i->delta_x) {
		y = (*(i->f))(x);
		integral += (prev_y + y) * i->delta_x / 2.0;
		prev_y = y;
	}
	
	return integral;
}

