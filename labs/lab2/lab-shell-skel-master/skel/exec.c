#include "exec.h"

// sets the "key" argument with the key part of
// the "arg" argument and null-terminates it
static void get_environ_key(char* arg, char* key) {
	printf("entro al get environ key \n");
	printf("arg: %s\n:",arg);	
	int i;
	for (i = 0; arg[i] != '='; i++)
		key[i] = arg[i];

	key[i] = END_STRING;
	printf("key: %s\n",key);
}

// sets the "value" argument with the value part of
// the "arg" argument and null-terminates it
static void get_environ_value(char* arg, char* value, int idx) {
	printf("entro al get environ value \n");
	printf("arg: %s\n:",arg);
	printf("idx: %d\n:",idx);
	int i, j;
	for (i = (idx + 1), j = 0; i < strlen(arg); i++, j++)
		value[j] = arg[i];

	value[j] = END_STRING;
	printf("value: %s\n", value);
}

// sets the environment variables passed
// in the command line
//
// Hints:
// - use 'block_contains()' to
// 	get the index where the '=' is
// - 'get_environ_*()' can be useful here
static void set_environ_vars(char** eargv, int eargc) {
	
	printf("entro \n");
	pid_t p;
	int status = 0;
	if ((p = fork()) == 0) {
		for(int i = 0 ; i <= eargc ; i++){
			printf("entro al fork y al for \n");
			char key[100];
			char* pKey = key;
			get_environ_key(eargv[i],pKey);
			printf("key: %s\n:",key);	
			int posicionIgual = block_contains(eargv[i],'=');	
			char value[100];
			char* pValue = value;
			get_environ_value(eargv[i], pValue, posicionIgual);
			printf("value: %S\n",value);
			int res =setenv(key ,value , 0 );
			if(res < 0){
				perror("setenv() error");
			}else{printf("en teoria la seteo \n");};
		}
	}	

} 

// opens the file in which the stdin/stdout or
// stderr flow will be redirected, and returns
// the file descriptor
// 
// Find out what permissions it needs.
// Does it have to be closed after the execve(2) call?
//
// Hints:
// - if O_CREAT is used, add S_IWUSR and S_IRUSR
// 	to make it a readable normal file
static int open_redir_fd(char* file) {

	// Your code here
	return -1;
}

// executes a command - does not return
//
// Hint:
// - check how the 'cmd' structs are defined
// 	in types.h
void exec_cmd(struct cmd* cmd) {

	switch (cmd->type) {

		case EXEC: {
			// spawns a command
			//if( block_contains(cmd->scmd,"=") > 0){
			if(((struct execcmd*)cmd)->eargc > 0){
				printf("en teoria empieza a setear variavles \n");
				char* eargv =((struct execcmd*)cmd)->eargv;
			        int cantEarg = ((struct execcmd*)cmd)->eargc;				
				set_environ_vars(eargv,cantEarg);
			};						
				
			char const  *fileName=((struct execcmd*)cmd)->argv[0];
			char *  const *argv =((struct execcmd*)cmd)->argv; 		

                        if(execvp(fileName,argv) < 0){
				//Agrego manejo de errores.
				perror("execvp() error");
			};
			_exit(-1);
			break;
		}
		case BACK: {
			// runs a command in background
			cmd->type = EXEC;
			exec_cmd(cmd);				
			_exit(-1);
			break;
		}

		case REDIR: {
			// changes the input/output/stderr flow
			//
			// Your code here
			printf("Redirections are not yet implemented\n");
			_exit(-1);
			break;
		}
		
		case PIPE: {
			// pipes two commands
			//
			// Your code here
			printf("Pipes are not yet implemented\n");
				
			// free the memory allocated
			// for the pipe tree structure
			free_command(parsed_pipe);

			break;
		}
	}
}

