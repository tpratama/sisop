#include <stdio.h>
#include <pthread.h>

void *run(void *args){
	int i=0, flag=0, *input;
	input = (int *)args;
        for(i=2;i<=*input;i++){
		if(*input%i==0)flag++;
	}
	if(*input == 1) printf("bukan prima\n");
	else if(flag==1)printf("%d --> prima\n",*input);
	else printf("%d --> bukan prima\n",*input);
}

void main(){
        pthread_t t1;
	int input,i;
	scanf("%d", &input);
	for(i=0;i<input;i++){
		pthread_create(&t1, NULL, run, (void*)&i);
        	pthread_join(t1, NULL);
	}
}
