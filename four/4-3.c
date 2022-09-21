#include "apue.h"

int main(int argc, char* argv[]){
	int i;
	struct stat buf;
	char *ptr;

	printf("%d\n", argc);	
	printf("%s\n", argv[0]);
	
	printf("================\n");
	for(i=1; i<argc;i++){
		printf("%s, ", argv[i]);
		if(lstat(argv[i], &buf) <0){
			printf("lstat errir");
			continue;
		}

		if(S_ISREG(buf.st_mode))
			ptr="regular";
		else if(S_ISDIR(buf.st_mode))
			ptr="directory";
		else if(S_ISBLK(buf.st_mode))
			ptr="block special";
		else if(S_ISFIFO(buf.st_mode))
			ptr="fifo";
		else if(S_ISLNK(buf.st_mode))
			ptr="socket";
		else
			ptr="**unknown mode*";
		printf("%s\n", ptr);
	}	

	exit(0);
}
