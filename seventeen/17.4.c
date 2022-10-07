#include "apue.h"
static void sig_pipe(int);

int main(){
	int n;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	if(signal(SIGPIPE, sig_pipe)==SIG_ERR)
		printf("signal error\n");

	if(s_pipe(fd) <0)
		printf("pipe error");
	if((pid=fork()) <0)
		printf("pipe error");
	else if(pid >0){
		close(fd[1]);
		while(fgets(line, MAXLINE, stdin) != NULL){
			n = strlen(line);
			printf("n: %d\n",n);
			if(write(fd[0], line ,n) != n)
				printf("write error to pipe\n");
			if(n==0){
				printf("child closed pipe");
				break;
			}
			line[n] = 0;
			if(fputs(line, stdout) == EOF)
				printf("fputs error");
		}
		if(ferror(stdin))
			printf("fgets error");
		exit(0);
	}else{
		close(fd[0]);
		if(fd[1] != STDIN_FILENO && dup2(fd[1], STDIN_FILENO) != STDIN_FILENO)
			printf("dup2 error to stdin");
		if(fd[1] != STDOUT_FILENO &*& dup(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
			printf("dup2 error to stdout");
		if(execl("./add2", "add2", (char*)0)<0)
			printf("execl error");
	}
	exit(0);
}

static void sig_pipe(int signo){
	printf("SIGPIPE caought\n");
	exit(1);
}
