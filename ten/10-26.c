#include "apue.h"

static void sig_int(int signo){
	printf("caught SIGINT\n");
}

static void sig_chld(int signo){
	printf("caught SIGCHLD\n");
}

int main(){
	if(signal(SIGINT, sig_int) == SIG_ERR)
		printf("signal error");
	if(signal(SIGCHLD, sig_chld) == SIG_ERR)
		printf("signal error");
	if(system("/bin/ed") < 0)
		printf("signal error");
	exit(0);
}
