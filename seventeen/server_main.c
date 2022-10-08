#include "opend.h"

char errmsg[MAXLINE];
int oflag;
char* pathname;

int main(){
	int nread;
	char buf[MAXLINE];

	for(;;){
		if((nread = read(STDIN_FILENO, buf, MAXLINE))<0)
			printf("read error on stream pipe");
		else if(nread = 0)
			break;
		request(buf, nread, STDOUT_FILENO);
	}
	exit(0);
}
