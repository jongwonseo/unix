#include "apue.h"

int main(){
	if(chdir("/tmp")<0)
		printf("no");
	printf("success");
	exit(0);
}
