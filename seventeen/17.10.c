#include "apue.h"
#include <fcntl.h>
#include <stropts.h>

#define FIFO_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int serv_listen(const char* name){
	int tempfd;
	int fd[2];

	unlike(name);
	if((tempfd = creat(name, FIFO_MODE))<0)
		return -1;
	if(close(tempfd)<0)
		return -2;
	if(pipe(fd)<0)
		return -3;

	if(ioctl(fd[1], I_PUSH, "connld")<0){
		close(fd[0]);
		close(fd[1]);
		return -4;
	}
	if(fattach(fd[1], name) <0){
		close(fd[0]);
		close(fd[1]);
		return -5;
	}
	close(fd[1]);

	return fd[0];
}
