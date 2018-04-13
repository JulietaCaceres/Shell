#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void tee0(const char *file) {
   char * buff = malloc(512);
   int fd = open(file,O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR);
   ssize_t size = read(0,buff,2048);
   size_t algo =  write(1,buff,size);
   size_t algo2 = write(fd,buff,size);
   close(fd);
}
int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    tee0(argv[1]);
    return 0;
}
