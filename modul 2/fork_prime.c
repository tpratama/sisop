#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void find_prime(int x){
int i;
if (x==1){
printf ("1 -BUKAN PRIMA\n");
exit(0);
}
	for(i=2;i<x;i++){
		if (x%i==0) {
		printf("%d -BUKAN PRIMA\n",x);
		exit(0);
		}
	}
	printf("%d - PRIMA\n",x);
	exit(0);
}

int main(){
int temp;

while(scanf("%d",&temp)!=EOF){
	if (fork()) find_prime(temp);
	else exit(0);		
}

return 0;
}

