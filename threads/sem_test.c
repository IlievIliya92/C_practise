#include <stdio.h>
#include <semaphore.h>

int main(void) {
	sem_t sem;
	int val;
	
	sem_init(&sem, 0, 2);
	sem_getvalue(&sem, &val);
	printf("1 %d\n", val);
	sem_wait(&sem);
	sem_getvalue(&sem, &val);
	printf("2 %d\n", val);
	sem_wait(&sem);
	sem_getvalue(&sem, &val);
	printf("3 %d\n", val);
	sem_post(&sem);
	sem_getvalue(&sem, &val);
	printf("4 %d\n", val);
	sem_wait(&sem);
	sem_getvalue(&sem, &val);
	printf("5 %d\n", val);
	printf("done\n");
	return 0;
}
