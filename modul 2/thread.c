#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *run(void *args){
	int i=0;
	for (i=1;i<=30;i++){
		printf("Thread 1 : %d\n",i);
	}
}

void *run2(void *args){
	int i=0;
	for(i=1;i<=30;i++){
		printf("Thread 2: %d\n",i);
	}
}

int main(){
	pthread_t t1,t2;
	pthread_create(&t1,NULL,run,NULL);
	pthread_create(&t2,NULL,run2,NULL);

	int i;
	for(i=1;i<=100;i++){
		printf("Main\n");
	}
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}
