#include "apue.h"
#include <errno.h>

#define CS_OPEN "/home/sar/opend"
#define CL_OPEN "open"

extern int debug;
extern char errmsg[];
extern char* pathname;
extern int oflag;

typedef struct{
	int fd;
	uid_t uid;
}Client;

extern Client *client;
extern int client_size;

int cli_args(int, char**);
int client_add(int, uid_t);
void client_del(int);
void loop();
void request(char*, int, int, uid_t);
