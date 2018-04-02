#define _POSIX_C_SOURCE 200809L

#include <unistd.h>

void rm0(const char *file) {
    //precondition: El archivo existe y es de tipo regular.
    unlink(file);
}

int main(int argc, char *argv[]) {
    //precondition: n° de argumentos correctos
    rm0(argv[1]);   
    return 0;
}
