#include "./dot_graph_io.h"

#ifdef _WIN32

#include <fcntl.h>
#include <io.h>

int ts_dot_graph_io_make_fd(HANDLE handle) {
  HANDLE dup_handle;
  DuplicateHandle(
    GetCurrentProcess(),
    handle,
    GetCurrentProcess(),
    &dup_handle,
    0,
    FALSE,
    DUPLICATE_SAME_ACCESS
  );
  return _open_osfhandle((intptr_t)dup_handle, _O_TEXT);
}

FILE* ts_dot_graph_io_open(int fd) {
  return _fdopen(fd, "a");
}

#else

#include <unistd.h>

int ts_dot_graph_io_make_fd(int fd) {
  return dup(fd);
}

FILE* ts_dot_graph_io_open(int fd) {
  return fdopen(fd, "a");
}

#endif

int ts_dot_graph_io_close(FILE* file) {
  return fclose(file);
}
