#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int end_of_file=0;
void *thread1(void* args){
   char* nama_file=(char*)args; 
   char karakter;
   FILE *in,*out;
   in=fopen(nama_file,"r");
   out=fopen("salinan.txt","w");
   while(fscanf(in,"%c",&karakter)!=EOF){
   	printf("Thread 1-->%c\n",karakter);
	fprintf(out,"%c",karakter);
   }
   fprintf(out,"#");
   //end_of_file=1;
   fclose(in);
   fclose(out);
}

void *thread2(void* args){ 
   FILE *in,*out;
   char karakter;
   
  in=fopen("salinan.txt","r");
  out=fopen("salinan2.txt","w");
  while(1){
	fscanf(in,"%c",&karakter);
        if (karakter=='#') break;
	printf("Thread 2--> %c\n",karakter);
	fprintf(out,"%c",karakter);
  }
  fclose(in);
  fclose(out);
}

int main(){
   pthread_t t1,t2;
   char nama_file[100];
   scanf("%s",nama_file); 
   pthread_create(&t1,NULL,thread1,(void*) &nama_file[0]);
   pthread_create(&t2,NULL,thread2,NULL);
   pthread_join(t1,NULL);
   pthread_join(t2,NULL);
   pthread_exit(0);
}
