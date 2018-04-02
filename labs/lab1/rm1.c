#define _POSIX_C_SOURCE 200809L

#include <unistd.h>

void rm1(const char *file) {
    //precondition: El archivo existe y es de tipo regular.
    int ret =  unlink(file);
    if (ret < 0){
    perror("remove() error");
} 
}

int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    rm1(argv[1]);   
    return 0;
}
