#include "apue.h"

static void sig_quit(int);

int main(){
	sigset_t newmask, oldmask, pendmask;
	
	if(signal(SIGQUIT, sig_quit) == SIG_ERR)
		printf("can`t catch SIGQUIT");

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("SIG_BLOCK error");

	sleep(5);
	if (sigpending(&pendmask) <0)
		printf("sigpending error");
	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) <0)
		printf("SIG_SETMASK error");
	printf("SIGQUIT unblocked\n");

	sleep(5);
	exit(0);
}

static void sig_quit(int signo){
	printf("caught SIGQUIT\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		printf("can`t reset SIGQUIT");
}
