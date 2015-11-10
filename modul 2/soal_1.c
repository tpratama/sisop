#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <dirent.h>

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

int main(){

	while(1){
		//ambil working dir
		getcwd(address,sizeof (address));
		printf("theo@theo-lenovo-G40-70 %s : ",address);		
		gets(cmd);
		//ambil command;
		token=strtok(cmd," ");
	
		//perintah cd
		if (strcmp("cd",token)==0) do_cd(token);
		//perintah ls
		if (strcmp("ls",token)==0) do_ls(token);	
	}
}
