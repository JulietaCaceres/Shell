#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void touch0(const char *file) {
   int fd =  open(file,O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR);
   close(fd);
}
int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    touch0(argv[1]);
    return 0;
}
