#include "apue.h"

int main(){
	char* name;

	if(isatty(0)){
		name = ttyname(0);
		if(name == NULL)
			name = "undefined";
	}else{
		name = "not a tty";
	}
	printf("fd 0: %s\n", name);
	
	if(isatty(1)){
		name = ttyname(1);
		if(name == NULL)
			name = "undefined";
	}else{
		name = "not a tty";
	}
	printf("fd 1: %s\n", name);

	if(isatty(3)){
		name = ttyname(3);
		if(name == NULL)
			name = "undefined";
	}else{
		name = "not a tty";
	}
	printf("fd 3: %s\n", name);
}
