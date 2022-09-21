#include "apue.h"
#include <fcntl.h>

int main(int argc, char* argv[]){
	int val;

	printf("%d\n", argc);

	if(argc!=2)
		printf("err\n");

	if((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
		printf("fcntl error for %d\n", atoi(argv[1]));

	switch(val & O_ACCMODE){
	case O_RDONLY:
		printf("read only");
		break;
	case O_WRONLY:
		printf("write only");
		break;
	case O_RDWR:
		printf("read write");
		break;
	default:
		printf("unknown access error");
	}

	if(val & O_APPEND)
		printf(", append");
	if(val & O_NONBLOCK)
		printf(", nonblocking");

#if defined(O_SYNC)
	if (val & O_SYNC)
		printf(", synchronous writers");

#endif

#if !defined(_POSIX_C_SOURCR) && defined(O_FSYNC)
	if (val & O_FSYNC)
		printf(", synchronous writer");
#endif
	putchar('\n');
	exit(0);
}
