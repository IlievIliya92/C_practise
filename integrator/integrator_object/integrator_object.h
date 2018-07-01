#ifndef _INTEGRATOR_OBJECT_
#define _INTEGRATOR_OBJECT_

typedef double (*function)(double);

void *integrator_create(double, double, double, function);
void integrator_destroy(void *);
double integrate(void *);

#endif
