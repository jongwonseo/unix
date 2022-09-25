#include "apue.h"

static void sig_usr(int);

int main(){
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
		printf("can't catch SIGUSR1");

	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
		printf("cna't catch sigusr2");
	
	for(;;)
		pause();
}

static void sig_usr(int signo){
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if(signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("received signal %d\n", signo);
}
