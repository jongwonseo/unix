#include <unistd.h>
#include <stdio.h>

int main(){
	printf("부모: %d  자식: %d\n", getppid(), getpid());
	return 0;
}
