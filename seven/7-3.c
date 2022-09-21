#include "apue.h"

static void my_exit1();
static void my_exit2();

int main(){
	if(atexit(my_exit2) != 0)
		printf("error 2");
	
	if(atexit(my_exit1) != 0)
		printf("error 1");
	
	printf("main is done\n");
	return (0);
}

static void my_exit1(){
	printf("first handler\n");
}

static void my_exit2(){
	printf("second handler\n");
}
