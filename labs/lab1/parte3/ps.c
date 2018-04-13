#include<unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

void ps0() {
	char *name = "/proc";
	char nameaaa[256] = "/proc\n";
	DIR *directoryStream =  opendir(name);
	struct dirent *algo = readdir(directoryStream);
	if(algo == NULL) {
		perror("remove() error");
	} else {
		printf("name: %s",nameaaa);
		printf("name: %s",algo->d_name);
	}
}
int main(int argc, char *argv[]) {
	//precondition: n° de argumentos correctos
	ps0(argv[1]);
	return 0;
}
