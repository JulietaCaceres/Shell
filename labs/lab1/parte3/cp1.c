#include<unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
void cp1(const char *oldFile, const char *newFile) {
	int oldfd = open(oldFile,O_RDONLY);
	size_t filesize = lseek(oldfd,0,SEEK_END);
	char *src = mmap(NULL,filesize,PROT_READ,MAP_PRIVATE,oldfd,0);
	int newfd = open(newFile,O_RDWR|O_CREAT,2048);
        ftruncate(newfd,filesize);
        char *dest = mmap(NULL,filesize,PROT_READ | PROT_WRITE, MAP_SHARED, newfd,0);
	memcpy(dest,src,filesize);
	munmap(src,filesize);
	munmap(dest,filesize);
	close(oldfd);
	close(newfd);
           
}
int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    cp1(argv[1],argv[2]);
    return 0;
}
