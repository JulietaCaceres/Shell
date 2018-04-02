#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void ln0(const char *oldpath, const char *newpath) {
   int state = symlink(oldpath,newpath);
}
int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    ln0(argv[1],argv[2]);
    return 0;
}
