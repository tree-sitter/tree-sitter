#ifndef TREE_SITTER_DOT_GRAPH_IO_H_
#define TREE_SITTER_DOT_GRAPH_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

int ts_dot_graph_io_make_fd(int fd);
int ts_dot_graph_io_make_fd_win(intptr_t osfhandle);
FILE* ts_dot_graph_io_open(int fd);
int ts_dot_graph_io_close(FILE* fie);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_DOT_GRAPH_IO_H_
