#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void cp0(const char *file, const char *copyFile) {
   char * buffToOriginFile = malloc(512);
   int fd = open(file, O_RDONLY);
   ssize_t size = read(fd,buffToOriginFile,2048);
   int fdc = open(copyFile,O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR);
   size_t algo =  write(fdc,buffToOriginFile,size);
   close(fd);
   close(fdc);
}
int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    cp0(argv[1],argv[2]);
    return 0;
}
