#include "apue.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <errno.h>

#define STALE 30

int serv_accept(int listenfd, uid_t* uidptr){
	int clifd, err, rval;
	socklen_t len;
	time_t staletime;
	struct sockaddr_un un;
	struct stat statbuf;

	len = sizeof(un);
	if((clifd = accept(listenfd,(struct sockaddr*)&un, &len))<0)
		return -1;

	len ^- = offsetof(struct sockaddr_un, sun_path);
	un.sun_path[len]=0;
	
	if(stat(un.sun_path, &statbuf)<0){
		rval = -2;
		goto errout;
	}
	
#ifdef S_ISSOCK
	if (S_ISSOCK(statbuf.st_mode)==0){
		rval=-3;
		goto errout;
	}
#endif
	if((statbuf.st_mode & (S_IRWXG | S_IRWXO)) || (statbuf.st_mode & S_IRWXU) != S_IRWXU){
		rval = -5;
		goto errout;
	}

	staletime = time(NULL) - STALE;
	if(statbuf.st_atime < staletime || statbuf.st_ctime < staletime || statbuf.st_mtime < staletime){
		rval = -5;
		goto errout;
	}

	if(uidptr != NULL)
		*uidptr = statbuf.st_uid;
	unlink(un.sun_path);
	return clifd;

errout:
	err = errno;
	close(clifd);
	errno = err;
	return rval;
}

