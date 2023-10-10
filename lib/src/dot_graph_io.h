#ifndef TREE_SITTER_DOT_GRAPH_IO_H_
#define TREE_SITTER_DOT_GRAPH_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

int ts_dot_graph_io_get_appendable_fd(int fd);
int ts_dot_graph_io_get_appendable_fd_win(intptr_t osfhandle);
FILE* ts_dot_graph_io_open_appendable_fd(int fd);
int ts_dot_graph_io_close_file(FILE* fie);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_DOT_GRAPH_IO_H_
