#include "apue.h"
#include <sys/wait.h>

char* env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(){
	pid_t pid;

	if((pid=fork()) <0)
		printf("fork error");
	else if(pid == 0){
		if(execle("/home/sar/bin/echoall", "echoall", "myarg1", "MY ARG2", (char*)0, env_init) <0)
			printf("execle error");
	}

	if(waitpid(pid, NULL, 0) <0)
		printf("wait error");

	if((pid = fork()) <0)
		printf("wait error");
	else if(pid==0){
		if(execlp("echoall", "echoall", "omly 1 arg", (char*)0) <0)
			printf("execlp error");
	}
	
	exit(0);
}
