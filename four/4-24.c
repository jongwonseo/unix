#include "apue.h"

int main(){
	char* ptr;
	int size;

	if(chdir("/usr/spool/uucppublic")<0)
		printf("chdir failed");

	ptr = path_alloc(&size);
	if(getcwd(ptr, size)==NULL)
		printf("getcwd failed");

	printf("cwd = %s\n", ptr);
	exit(0);:
}
