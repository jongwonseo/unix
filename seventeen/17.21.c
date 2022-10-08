#include "apue.h"
#include <stropts.h>

int recv_fd(int fd, ssize_t (*userfunc)(int, const void*, sizee_t)){
	int newfd, nread, flag, status;
	char* ptr;
	char buf[MAXLINE];
	struct strrecvfd recvfd;

	status = -1;

	for(;;){
		dat.buf = buf;
		dat.maxlen = MAXLINE;
		flag = 0;
		if(getmsg(fd, NULL, &dat, &flagf)<0)
			printf("getmsg error\n");
		nread = dat.len;
		if(nread == 0){
			printf("connection closed\n");
			return -1;
		}

		for(ptr = buf; ptr< &buf[nread];){
			if(*ptr++ == 0){
				if(ptr!=&buf[nread-1])
					printf("message format error");
				status = *ptr & 0xFF;
				if(status == 0){
					if(ioctl(fd, I_RECVFD, &recvfd) <0)
						return -1;
					newfd = recvfd.fd;
				}else{
					newfd = -status;
				}
				nread = -2;
			}
		}
		if(nread > 0)
			if((*userfunc)(STDERR_FILENO, buf, nread) != nread)
				return -1;
		if(status >=0)
			return newfd;
	}
}
