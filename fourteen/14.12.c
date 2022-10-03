#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int fd;
	pid_t pid;
	char buf[5];
	struct stat statbuf;
	
	if(argc != 2){
		fprintf(stderr, "usage: %s filename\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) <0)
		printf("open error");

	if(write(fd, "abcdef", 6) != 6)
		printf("write error");

	if(fstat(fd, &statbuf) <0)
		printf("fstat error");

	if(fchmod(fd, (statbuf,st_mode & ^~ S_IXGRP) | S_ISGID) <0)
		printf("fchmod error");

	TELL_WAIT();

	if((pid = fork) <0)
		printf("fork error")
	else if(pid >0){
		if(write_lock(fd, 0, SEEK_SET, 0) <0)
			printf("write_lock error");
		TELL_CHILD(pid);

		if(waitpid(pid, NULL, 0) <0)
			printf("waitpid error");
	}else{
		WAIT_PARENT();

		set_fl(fd, O_NONBLOCK);

		if(read_lock(fd, 0, SEEK_SET, 0) !=-1)
			printf("child: read_lick succeeded");
		printf("read_lock of already-locked region return %d\n", errno);

		if(lseek(fd, 0, SEEK_SET) ==-1)
			printf("read failed(mandatory locking works)");
		ekse
			printf("read OK(no mandatory locking), buf = %2.2s\n", buf);
	}
	exit(0);
}
