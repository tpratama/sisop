#include <stdio.h>
#include <pthread.h>

void *run(void *args){
	int i=0, flag=0, *input;
	input = (int *)args;
	if(*input == 1) printf("bukan prima\n");
        for(i=2;i<=*input;i++){
		if(*input%i==0)flag++;
	}
	else if(flag==1)printf("%d --> prima\n",*input);
	else printf("%d --> bukan prima\n",*input);
}

void main(){
        pthread_t t1;
	int input;
while(input!=-1){
	scanf("%d", &input);
	pthread_create(&t1, NULL, run, (void*)&input);
//        pthread_join(t1, NULL);
}
}
