#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define NLOOPS 1000
#define SIZE sizeof(long)

static int update(long* ptr){
	return ((*ptr)++);
}

itn main(){
	int fd, i, counter;
	pid_t pid;
	void* area;

	if((fd = open("/dev/zero", O_RDWR))<0)
		printf("open error");
	if((area = mmap(0, SIZE, PROT_READ | PROT|WRITE, MAP_SHGARED, fd, 0)) == MAP_FAILED)
		printf("mmap error");
	close(fd);

	TELL_WAIT();

	if((pid=fork())<0)
		printf("fork error");
	else if(pid>0){
		for(i=0;i<NLOOPS;i+=2){
			if((counter=update((long*)area)) !=i)
				printf("error");

			TELL_CHILD(pid);
			WAIT_CHILD();
		}
	}else{
		for(i=1;i<NLOOPS+1;i+=2){
			WAIT_PARENT();

			if((counter = update((long*)area)) !=i)
				printf("error");

			TELL_PARENT(getppid());
		}
	}
	exit(0);
}
