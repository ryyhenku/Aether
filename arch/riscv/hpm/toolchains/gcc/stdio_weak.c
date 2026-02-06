#include <stdio.h>

//使用newlib时，发现当前的RISCV工具链会报下面这些接口的链接错误
//先暂时在这里把缺失的系统调用实现空 

int __attribute__((weak)) _write(int file, char *ptr, int len)
{
    return 0;
}


 int __attribute__((weak)) _read(int file, char *ptr, int len) {
    return 0;
}

 int __attribute__((weak))  _close(int file) {
    return 0;
}

int __attribute__((weak))  _fstat(int file, struct stat *st) {
    return 0;
}

int __attribute__((weak))  _isatty(int file) {
    return 0;
}

int __attribute__((weak))  _lseek(int file, int offset, int whence) {
    return 0;
}


void __attribute__((weak))  *_sbrk(intptr_t incr) {
    return 0;
}

int __attribute__((weak))  _getpid(void) {
    return 0;
}

int __attribute__((weak))  _kill(int pid, int sig) {
    return 0;
}

void __attribute__((weak))  _exit(int status) {
    return 0;
}

pid_t __attribute__((weak))  _fork(void) {
    return 0;
}

pid_t __attribute__((weak))   _wait(int *status) {
    return 0;
}