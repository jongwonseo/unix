#include "apue.h"
#include <errno.h>
#include <fcntl.h>

char buf[500000];

int main(){
	int ntowrite ,nwrite;
	char* ptr;

	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d nytes\n", ntowrite);

	set_fl(STDOUT_FILENO, O_NONBLOCK);

	ptr = buf;
	while(ntowrite >0){
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);

		if(nwrite >0){
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}

	clr_fl(STDOUT_FILENO, O_NONBLOCK);
	
	exit(0);
}


