#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 8192

int main(int argc, char* argv[]){
	int n, fd;
	char buf[BUFFSIZE], line[MAXLINE];

	while(fgets(line, MAXLINE, stdin) != NULL){
		if(line[strlen(line)-1] == '\n')
			line[strlen(line)-1]=0;
		
		if((fd = csopen(line, O_RDONLY)) <0)
			continue;

		while((n = read(fd, buf, BUFFSIZE)) >0)
			if(write(STDOUT_FILENO, buf, n) != n)
				printf("write error");
		if(n<0)
			printf("read only");
		clse(fd);
	}

	exit(0);
}
