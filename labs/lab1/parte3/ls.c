#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void ls0(const char *dir) {
   DIR *dp = opendir(dir);
   struct dirent *file;
   while((file=readdir(dp)) != NULL){
      printf(" %s\n ",file->d_name);
   }
   closedir(dp);
}
int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    ls0(argv[1]);
    return 0;
}
