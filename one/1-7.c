#include "apue.h"
#include <sys/wait.h>

int main(){
	char buf[MAXLINE];
	pid_t pid;
	int status;

	printf("%% ");
	while(fgets(buf, MAXLINE, stdin) != NULL){
		if(buf[strlen(buf) -1] == "\n")
			buf[strlen(buf)-1] = 0;

		if((pid = fork()) < 0 ){
			printf("fork error");
		}else if(pid == 0){
			execlp(buf, buf,(char *)0);
			printf("couldn't execute: %s", buf);
			exit(127);
		}

		if ((pid=waitpid(pid, &status, 0)) < 0)
			printf("waitpid err");
		printf("%%");
	}
	exit(0);
}
