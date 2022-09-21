#include <stdio.h>
#include <unistd.h>

int main(){
	execlp("ls", "ls", "-al", "/tmp", NULL);
	printf("이 메세지가 보이면 지정된 프로그램이 없거나 실행되지 못한 것임\n");
}
