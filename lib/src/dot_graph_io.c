#ifdef _WIN32

#include <fcntl.h>
#include <io.h>
#include <stdio.h>

int ts_dot_graph_io_get_appendable_fd(int fd) {
  (void)fd;
  return -1;
}

int ts_dot_graph_io_get_appendable_fd_win(intptr_t osfhandle) {
  return _open_osfhandle(osfhandle, _O_APPEND | _O_TEXT);
}

FILE* ts_dot_graph_io_open_appendable_fd(int fd) {
  return _fdopen(fd, "a");
}

int ts_dot_graph_io_close_file(FILE* file) {
  return _close(file);
}

#else

#include <stdio.h>
#include <unistd.h>

int ts_dot_graph_io_get_appendable_fd(int fd) {
  return dup(fd);
}

int ts_dot_graph_io_get_appendable_fd_win(intptr_t osfhandle) {
  (void)osfhandle;
  return -1;
}

FILE* ts_dot_graph_io_open_appendable_fd(int fd) {
  return fdopen(fd, "a");
}

int ts_dot_graph_io_close_file(FILE* file) {
  return fclose(file);
}

#endif
