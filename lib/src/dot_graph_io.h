#ifndef TREE_SITTER_DOT_GRAPH_IO_H_
#define TREE_SITTER_DOT_GRAPH_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#ifdef _WIN32

#include <windows.h>

int ts_dot_graph_io_make_fd(HANDLE handle);

#else

int ts_dot_graph_io_make_fd(int fd);

#endif

FILE* ts_dot_graph_io_open(int fd);
int ts_dot_graph_io_close(FILE* file);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_DOT_GRAPH_IO_H_
