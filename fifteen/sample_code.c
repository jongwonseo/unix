#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]){
	FILE* r_fp;
	char buff[2048+1];
	int rtn = 0;

	memset(buff, 0x00, sizeof(buff));
	r_fp = popen("pwd", "r");
	if(!r_fp){
		printf("error");
		return -1;
	}

	rtn = fread(buff, sizeof(char), sizeof(buff), r_fp);
	if(rtn>0)
		printf("read: %s\n", buff);

	pclose(r_fp);

	return -1;
}
