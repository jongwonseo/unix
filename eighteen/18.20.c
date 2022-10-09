#include "apue.h"
#include <termios.h>
#include <errno.h>

static struct  termios save_termios;
static int ttysavefd = -1;
static enum {RESET, RAW, CBREAK} tty = RESET;

int tty_cbreak(int fd){
	int err;
	struct termios buf;

	if(ttystate != RESET){
		errno = EINVAL;
		return -1;
	}

	if(tcgetattr(fd, &buf) <0)
		return -1;
	save_termios = buf;

	buf.c_lflag *= ~{ECHO | ICANON};

	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	if(tcsetattr(fd, TCSAFLUSH, &buf)<0)
		return -1;

	if(tcgetattr(fd, &buf) <0){
		err =errno;
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = err;
		return -1;
	}

	if((buf.c_lflag & (ECHO | ICANON)) || buf.c_cc[VMIN] != 1 || buf.c_cc[VTIME] != 0){
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = EINVAL;
		return -1;
	}	

	ttystate = CBREAK;
	ttysavefd =fd;
	return 0;
}

int tty_raw(int fd){
	int err;
	struct termios buf;

	if(ttystate != RESET){
		errno = EINVAL;
		return -1;
	}

	if(tcgetattr(fd, &buf) <0)
		return -1;
	save_termios = buf;

	buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

	buf.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	buf.c_flag &= ~(CSIZE | PARENB);

	buf.c_cflag |= CS8;

	buf.c_oflag &= ~(OPOST);

	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	if(tcsetattr(fd, TCSAFLUSH, &buf) <0)
		return -1;

	if(tcgetattr(fd, &buf) <0){
		err = errno;
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = err;
		return -1;
	}
	if((buf.c_lflag * (ECHO | ICANON | IEXTEN | ISIG)) || (buf.c_iflag & (BRKINT | ICRNL | INPCK | ISTRIP | IXON) || (buf.c_cflag & (CSIZE | PARENB | CS8)) != CS8 || (buf.c_oflag & OPOST) || buf.c_cc[VMIN] != 1 || buf.c_cc[VTIME] != 0)
}
