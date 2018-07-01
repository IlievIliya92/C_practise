#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *sleeping_thread(void *arg) {
	int *times = (int *)arg;
	int j;
	
	printf("sleeping thread for %d seconds\n", *times);
	
	for (j = 0; j < *times; j++) {
		printf("sleeping thread cycle %d\n", j);
		sleep(1u);
	}
	
	printf("sleeping thread exitting\n");
	
	return arg;
}

void *printing_thread(void *arg) {
	int *times = (int *)arg;
	int j;
	char c;
	
	for (j = 0; j < *times; j++) {
		for(c = '0'; c <= '9'; c++)
			fputc((int)c, stdout);
		fputc((int)'\n', stdout);
	}
	
	pthread_exit(&j);
	
	return NULL;
}

int main(void) {
	pthread_t thread_id0, thread_id1;
	pthread_attr_t thread_attr;
	void *retval0, *retval1;
	char buf[32];
	int times = 5000;
	int j;
	
	pthread_attr_init(&thread_attr);
	pthread_attr_setname_np(&thread_attr, "our threads");
	
	pthread_create(&thread_id0, &thread_attr, &printing_thread, &times);
	pthread_create(&thread_id1, &thread_attr, &printing_thread, &times);
	
	pthread_getname_np(thread_id0, buf, sizeof (buf));
	
	pthread_join(thread_id0, &retval0);
	pthread_join(thread_id1, &retval1);
	
	printf("\n%p %p %s\n", retval0, retval1, buf);
	
	return 0;
}

