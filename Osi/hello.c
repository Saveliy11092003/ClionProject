#include <unistd.h>
#include <sys/syscall.h>
#include "stdlib"

enum Consts {
    STDOUT = 1,
    COUNT_BYTE_IN_BUFFER = 13,
    EXIT_SUCCESS = 0,
    EXIT_FAILURE = -1
};

ssize_t mywrite(int fd, const char* buf, size_t count) {
    return syscall(SYS_write, fd, buf, count);
}

int main(){

    mywrite(STDOUT, "Hello world!\n", COUNT_BYTE_IN_BUFFER);

    return EXIT_SUCCESS;
}
