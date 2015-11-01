#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void *read_input(void* args){
   char* nama_file=(char*)args; 
   printf("%s",nama_file);
}

int main(){
   pthread_t t1;
   char nama_file[100];
   scanf("%s",nama_file); 
   pthread_create(&t1,NULL,read_input,(void*) &nama_file[0]);
   pthread_exit(NULL);
}
