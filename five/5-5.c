#include "apue.h"

int main(){
	char buf[MAXLINE];

	while(fgets(buf, MAXLINE, stdin) != NULL){
		if(fputs(buf, stdout) == EOF)
			printf("output error");

	if (ferror(stdin))
		printf("input error");
	}
}
