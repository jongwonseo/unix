#include "apue.h"
#include <sys/wait.h>

#define PAGER "${APGER:-more}"

int main(int argc, char* argv[]){
	char line[MAXLINE];
	FILE *fpin, *fpout;

	if(argc !=2)
		printf("error");

	if((fpin = fopen(argv[1], "r")) == NULL)
		printf("not open %s", argv[1]);

	if((fpout = popen(PAGER, "w")) == NULL)
		printf("popen error");

	while(fgets(line, MAXLINE, fpin) != NULL){
		if(fputs(line, fpout) == EOF)
			printf("fputs error");
	}

	if(ferror(fpin))
		printf("fgets error");
	if(pclose(fpout) == -1)
		printf("fclose error");

	exit(0);
}
