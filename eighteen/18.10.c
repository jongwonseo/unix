#include "apue.h"
#include <termios.h>

int main(){
	struct termios term;
	long vdisable;

	if(isatty(STDIN_FILENO) == 0)
		printf("standard input is not a terminal device");
	if((vdisable = fpathconf(STDIN_FILENO, _PI_VDISABLE)) <0)
		printf("fpathconf error or _POSIX_VDISABLE not in effect");

	if(tcgetattr(STDIN_FILENO, &term) <0)
		printf("tcgetattr error");

	term.c_cc[VINTR] = vdisable;
	term.c_cc[VEOF] = 2;

	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) <0)
		printf("tcsetattr error");

	exit(0);
}
