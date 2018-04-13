#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void cat0(const char *file) {
   char * buff = malloc(512);
   int fd = open(file, O_RDONLY);
   ssize_t size = read(fd,buff,2048);
   size_t algo =  write(1,buff,size);
   close(fd);
}
int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    cat0(argv[1]);
    return 0;
}
