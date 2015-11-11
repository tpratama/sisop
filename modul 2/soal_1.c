#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
//GLOBAL VARIABEL
char cmd[1024],address[1024],*token;
int sts;
DIR *directory;
struct dirent *file;
//END_OF_GLOBAL_VAR


int do_cd(char* token){
	token=strtok(NULL," ");
	//change dir ke inputan user;		
	sts=chdir(token);
	if (sts!=0) printf("Wrong command or path not found!\n");
}

int do_ls(char* token){

	char *temp_address=address;			
	int show_all=0;
	int error=0;

	while(token!=NULL){		
		token=strtok(NULL," ");
		//jika ada option -a maka show_all			
		if (token!=NULL && strcmp(token,"-a")==0) show_all=1;
			else if (token!=NULL){
				if (token[0]=='/') strcat(temp_address,token);
				else {
					printf("Syntax error\n");
					error=1;
					}
				}
			}
		if (error) return -1;			
		directory=opendir(temp_address);
		while((file=readdir(directory))!=NULL)
		{
		//ada . maka hidden, jika tidak show_all maka lanjut saja
			if (file->d_name[0]=='.' && !show_all) continue;
			else printf("%s\n",file->d_name);
		}

}

int do_all_command(char* cmd,char* token,int mode){
	token=strtok(NULL," ");
		
	char* argument[100];
	argument[0]=cmd;	
	int now=1;
	while(token!=NULL){
		argument[now]=token;
		now++;
		token=strtok(NULL," ");
	}
	argument[now]=NULL;
	pid_t pid=fork();
	if (pid==0) {
		int stat=execvp(argument[0],argument);
		if (stat==-1) printf("Syntax Error\n");		
		exit(errno);	
	}	
	else{
		if (mode==0) wait(0);
		else {
			printf("PID : %d\n",(int)pid);		
		}
	}

}

int do_signaling(){
	pid_t pid=getpid();
	kill(pid,SIGKILL);
}

int main(){
char* temp;

	while(1){
		memset(cmd,0,sizeof cmd);
		//ambil working dir
		getcwd(address,sizeof (address));
		printf("theo@theo-lenovo-G40-70 %s $ ",address);		
		gets(cmd);
		char eol_check=cmd[strlen(cmd)-1];
		//signaling CTRL+D
		if (eol_check==0) do_signaling();
		
		char* ampersand=NULL;
		int mode;
		char *command_list[1024];
		ampersand=strstr(cmd,"&");
		temp=strtok(cmd,"&");
		int now=0,i;
		while(temp!=NULL){
			command_list[now]=temp;
			now++;			
			temp=strtok(NULL,"&");
		}		
		now-=1;
		
		for(i=0;i<=now;i++){
			token=strtok(command_list[i]," ");

			if (ampersand!=NULL) mode=1;
			//perintah cd
			if (strcmp("cd",token)==0) do_cd(token);
			//perintah ls
			else if (strcmp("ls",token)==0) do_ls(token);	
			//perintah selain diatas
			else if (token!=NULL) do_all_command(token,command_list[i],mode);
			
		}
		
	}	
}
