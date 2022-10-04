#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_BUF 1024
#define READ 0
#define WRITE 1

int main(){
	int fdA[2], fdB[2];
	pid_t pid;
	char buf[MAX_BUF];
	int count= 0;

	if(pipe(fdA) <0 || pipe(fdB) <0){
		printf("pipe error");
		exit(1);
	}

	if((pid = fork()) <0){
		printf("fork error");
		exit(1);
	}

	if(pid >0){
		close(fdA[READ]);
		close(fdB[WRITE]);

		while(1){
			sprintf(buf, "parent %d", count++);
			write(fdA[WRITE], buf, MAX_BUF);
			memset(buf, 0, sizeof(buf));
			read(fdB[READ], buf, MAX_BUF);
			printf("parent get message: %s\n", buf);
			sleep(1);
		}
	}else{
		close(fdA[WRITE]);
		close(fdB[READ]);

		while(1){
			sprintf(buf, "child: %d", count++);
			write(fdB[WRITE], buf, MAX_BUF);
			memset(buf, 0, sizeof(buf));
			read(fdA[READ], buf, MAX_BUF);
			printf("child got message: %s\n", buf);
			sleep(1);
		}
	}
	exit(1);
}
