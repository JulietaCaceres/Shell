#include "builtin.h"

// returns true if the 'exit' call
// should be performed
int exit_shell(char* cmd) {
	if(strcmp(cmd,"exit") == 0){
		exit(0);
	}	
	return 0;
}

// returns true if "chdir" was performed
// this means that if 'cmd' contains:
// 	$ cd directory (change to 'directory')
// 	$ cd (change to HOME)
// it has to be executed and then return true
bool  cd(char* cmd) {
	char comando[100];
	char* pComando = strcpy(comando,cmd);
	char* directorio = split_line(pComando,' ');
	strcpy(comando,pComando);
	if(strcmp(comando,"cd")){return false;};
	if(!strcmp(comando,cmd)){
		char* home = "HOME";
		printf("home: %s\n:",home);
		directorio = getenv(home);
	}	
	int ret = chdir(directorio);
	if(ret < 0){ perror("chdir() error");};
	return ret == 0;
 }


// returns true if 'pwd' was invoked
// in the command line
int pwd(char* cmd) {
	if(strcmp(cmd,"pwd") == 0){
	char* buff;
	char* path = getwd(buff);
	printf(path);
	}
	return 0;
}

