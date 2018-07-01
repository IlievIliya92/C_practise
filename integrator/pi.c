#include <stdio.h>
#include <math.h>

#include "integrator_object.h"

double f(double x) {	
	return sqrt(1.0 - x * x);
}

int main(void) {
	void *integrator;
	double delta_x;
	double pi;
	
	scanf("%lf", &delta_x);
/*
	integrator = integrator_create(-1.0, 1.0, delta_x, &f);
*/
	integrator = integrator_create(0.0, M_PI / 2.0, delta_x, &sin);
	if (!integrator) return 1;
	
/*
	pi = 2.0 * integrate(integrator);
	printf("%0.10lf\n", pi);
*/
	printf("%0.10lf\n", integrate(integrator));
	
	integrator_destroy(integrator);
	
	return 0;
}

