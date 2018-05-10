#include "exec.h"

// sets the "key" argument with the key part of
// the "arg" argument and null-terminates it
static void get_environ_key(char* arg, char* key) {
		
	int i;
	for (i = 0; arg[i] != '='; i++)
		key[i] = arg[i];

	key[i] = END_STRING;
	
}

// sets the "value" argument with the value part of
// the "arg" argument and null-terminates it
static void get_environ_value(char* arg, char* value, int idx) {
	
	int i, j;
	for (i = (idx + 1), j = 0; i < strlen(arg); i++, j++)
		value[j] = arg[i];

	value[j] = END_STRING;
}

// sets the environment variables passed
// in the command line
//
// Hints:
// - use 'block_contains()' to
// 	get the index where the '=' is
// - 'get_environ_*()' can be useful here
static void set_environ_vars(char** eargv, int eargc) {
	
	pid_t p;
	int status = 0;
	if ((p = fork()) == 0) {
		for(int i = 0 ; i <= eargc ; i++){
			char key[100];
			char* pKey = key;
			get_environ_key(eargv[i],pKey);
			int posicionIgual = block_contains(eargv[i],'=');	
			char value[100];
			char* pValue = value;
			get_environ_value(eargv[i], pValue, posicionIgual);
			int res =setenv(key ,value , 0 );
			if(res < 0)
			  perror("setenv() error");
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
	
	int fd =  open(file,O_CREAT|O_WRONLY|O_TRUNC|O_RDONLY,S_IRUSR|S_IWUSR);
	return fd;
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
			if(((struct execcmd*)cmd)->eargc > 0){
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
			struct backcmd* cmdb = (struct backcmd*)cmd;
			exec_cmd(cmdb->c);				
			_exit(-1);
			break;
		}

		case REDIR: {
			
			struct execcmd* cmdr = (struct execcmd*)cmd;
                        char const  *fileName=cmdr->argv[0];
                        char *  const *argv = cmdr->argv;
                        if(strlen(cmdr->out_file)>0){
				printf("entro on \n");
				int fd = open_redir_fd(cmdr->out_file);	
				if( fd < 0)
                              	   perror("open() error");
				dup2(fd, STDOUT_FILENO);
				close(fd);
				
			}
			if(strlen(cmdr->in_file)>0){
				  
				printf("entro in \n");
				int fd =  open(cmdr->in_file,O_RDONLY);
                                if( fd < 0)
                                   perror("menor que cero");
				dup2(fd,STDIN_FILENO);
				close(fd); 
				
			}
			if(strlen(cmdr->err_file)>0){
				int fd;	
				int equals = strcmp(cmdr->err_file,"&1");
				printf("entro a error\n");	
				if(equals == 0){
				   	printf("entro a &\n");
					dup2(STDOUT_FILENO,STDERR_FILENO);
					
				}else{	
					printf("entro err\n");
					fd = open_redir_fd(cmdr->err_file);
					if(fd<0)
                       	                 perror("open() error");
				}	
				dup2(fd,STDERR_FILENO);
				close(fd);	
			
		      }	
			if(execvp(fileName,argv) < 0)
				perror("execvp() error");
	
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

