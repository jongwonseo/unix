#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo){
	struct passwd* rootptr;
	
	printf("in signal handler\n");
	if((rootptr = getpwnam("root")) == NULL)
		printf("getpwnam(root) error");

	alarm(1);
}

int main(){
	struct passwd* ptr;
	signal(SIGALRM, my_alarm);
	alarm(1);

	for(;;){
		if((ptr=getpwnam("whd7327")) == NULL)
			printf("getpwnam error");
		if(strcmp(ptr->pw_name, "whd7327") !=0)
			printf("returm value corrupted!, pw_name = %s\n", ptr->pw_name);
	}
}
