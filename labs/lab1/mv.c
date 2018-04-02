#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void mv0(const char *oldPath, const char *newPath) {
   rename(oldPath,newPath);
}
int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    mv0(argv[1],argv[2]);
    return 0;
}
