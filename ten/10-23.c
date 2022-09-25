#include "apue.h"

volatile sig_atomic_t quitflag;

static void sig_int(int signo){
	if(signo == SIGINT)
		printf("\ninterrupt\n");
	else if(signo == SIGQUIT)
		quitflag = 1;
}

int main(){
	sigset_t newmask, oldmask, zeromask;

	if(signal(SIGINT, sig_int) == SIG_ERR)
		printf("signla error");
	
	if(signal(SIGQUIT, sig_int) == SIG_ERR)
		printf("signal error");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigemptyset(&newmask, SIGQUIT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) <0)
		printf("SIG_BLOCK error");

	while(quitflag == 0)
		sigsuspend(&zeromask);

	quitflag=0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) <0)
		printf("SIG error");

	exit(0);
}
