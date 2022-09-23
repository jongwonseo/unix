#include "apue.h"
#include <sys/wait.h>

int main(){
	pid_t pid;
	if((pid=fork()) <0){
		printf("fork error");
	}else if(pid == 0){
		if (execl("/home/sar/bin/testinterp", "testinterp","myarg1", "MY ARG2", (char*)0) <0)
			printf("execl error");
	}

	if(waitpid(pid, NULL, 0) <0)
		printf("waitpid error");
	exit(0);
}
