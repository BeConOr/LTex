#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREAD_NMB 1000

long a = 0;

void *thread_start(void *args){
	int i;
	long tmp;
	
	for(i = 0; i < 100000; i++){
		tmp = a;
		tmp++;
		a = tmp;
	}
	
	return NULL;
}

int main(void){
	int index[THREAD_NMB];
	int i;
	int index1;
	int *s;
	pthread_t thread[THREAD_NMB];
	
	for(i = 1; i <= THREAD_NMB; i++){
		index[i-1] = i;
		pthread_create(&thread[i-1], NULL, thread_start, &index[i-1]);
	}
	
	for(index1 = 0; index1 < THREAD_NMB; index1++){
		pthread_join(thread[index1], (void **) &s);
	}
	
	printf("%ld\n", a);
	
	return 0;
}