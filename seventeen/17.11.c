#include "apue.h"
#include <stropts.h>

int serv_accept(int listenfd, uid_t* uidptr){
	struct strrecvfd recvfd;
	if(ioctl(listenfd, I_RECVFD, &recvfd) <0)
		return -1;
	if(uidptr != NULL)
		*uidptr = recvfd.uid;
	return recvfd.fd;
}
