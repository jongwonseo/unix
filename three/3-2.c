#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(){
	int fd;

	if((fd=creat("file.hole", FILE_MODE)) < 0)
		printf("create error");

	if(write(fd, buf1, 10) != 10)
		printf("buf1 write error");

	if(lseek(fd, 16384, SEEK_SET) == -1)
		printf("lseek error");

	if(write(fd, buf2, 10) != 10)
		printf("buf2 write error");

	exit(0);
}
