#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

void main(int argc, char* argv[]){
	DIR* od;
	struct dirent* dir;

	if((od = opendir(argv[1]))==NULL){
		perror("Fail");
		exit(1);
	}

	while((dir = readdir(od)) != NULL)
		printf("%s\n", dir->d_name);

	closedir(od);
}
