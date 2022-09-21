#include "apue.h"
#include <errno.h>
#include <limits.h>

int main(int argc, char* argv){
	if(argc != 2)
		err_quit("usageL a.out <dirname>");

#ifdef ARG_MAX
	printf("ARG_MAX defined to be %d\n", ARG_MAX + 0);

#else
	printf("no symbol for ARG_,AX\n");
#endif

#ifdef _SC_ARG_MAX
printf("ARG_MAX defined to be %d\n", _SC_ARG_MAX + 0);

#else
printf("no symbol for _SC_ARG_,AX\n");
#endif

#ifdef MAX_CANON
	printf("MAX_CANON defined to be %d\n", MAX_CANON + 0);

#else
	printf("no symbol for MAX_CANON\n");
#endif

#ifdef _PC_MAX_CANON
	printf("_PC_MAX_CANON defined to be %d\n", _PC_MAX_CANON + 0);

#else
	printf("no symbol for _PC_MAX_CANON\n");
#endif
	exit(0);

}

static void pr_sysconf(char *mesg, int name){
	long val;

	fputs(mesg, stdout);
	errno = 0;

	if((val=sysconf(name)) < 0){
		if (errno!=0){
			if(errno == EINVAL)
				fputs("(not supported)", stdout);
			else
				err_sys("sysconf error");
		}else{
			fputs("(no limit)\n", stdout);
		}
	}else
		printf("%ld\n", val);
}

static void pr_pathconf(char *mesg, char* path, int name){
	long val;
	fputs(mesg, stdout);
	errno = 0;
	if((val=pathconf(path,name))<0){
		if(errno !=0){
			if(errno==EINVAL)
				fputs("(not supported)\n", stdout);
			else
				err_sys("pathconf error, path=%s", path);
		}else{
			fputs("(no limit)\n", stdout);
		}
	}else{
		printf("%ld\n", val);
	}
}
