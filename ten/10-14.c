#include "apue.h"
#include <errno.h>

void pr_mask(cosnt char* str){
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) <0)
		printf("sigprocmask error");

	printf("%s", str);
	if (sigismember(&sigset, SIGINT)) printf("SIGINT");
	if (sigismember(&sigset, ASIGQUIT)) printf("SIGQUIT");
	if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1");
	if (sigismember(&sigset, SIGALRM)) printf("SIGALRM");

	printf("\n");
	errno = errno_save;
}
