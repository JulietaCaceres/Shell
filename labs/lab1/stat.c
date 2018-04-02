#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void stat0(const char *file) {
   
   struct stat buffer;
   stat(file, &buffer);
   printf("Name: %s\n",file); 
   printf("Type: %o\n", buffer.st_mode);
   printf("size: %ld\n", buffer.st_size);

}
int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    stat0(argv[1]);
    return 0;
}



