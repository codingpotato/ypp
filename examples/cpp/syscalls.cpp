#include <sys/types.h>

extern "C" {

int _read(int file, char *ptr, int len) {
  return len;
}

int _write(int file, char *ptr, int len) {
  return len;
}

void _exit(int status) {}

int _lseek(int file, int ptr, int dir) {
  return 0;
}

int _isatty(int fd) {
  return 0;
}

int _fstat(int file, struct stat *st) {
  return 0;
}

int _close(int file) {
  return 0;
}

int _getpid(int n) {
  return 0;
}

caddr_t _sbrk(int incr) {
  return 0;
}

int _kill(int pid, int sig) {
  return 0;
}
}
