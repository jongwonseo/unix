#include "apue.h"
#include <termios.h>

int main(){
	struct termios term;
	if(tcgetattr(STDIN_FILENO, &term) <0)
		printf("tcgetattr error");

	switch(term.c_cflag & CSIZE){
		case CS5:
			printf("5\n");
			break;
		case CS6:
			printf("6\n");
			break;
		case CS7:
			printf("7\n");
			break;
	
		case CS8:
			printf("8\n");
			break;
		default:
			printf("unknown bit\n");

	}

	term.c_cflag &= ~CSIZE;
	term.c_cflag |= CS8;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &term)<0)
		printf("tcsetattr error\n");
	exit(0);

}
