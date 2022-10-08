#include "apue.h"
#include <errno.h>

#define CL_OPEN "open"

extern char errmsg[];
extern char* pathname;
extern int oflag;

int cli_args(int, char**);
void request(char*, int, int);
