#if defined(TREE_SITTER_TEST)

void ts_record_free(void *);

void rust_tree_sitter_free(void *p) {
  ts_record_free(p);
}

#else

void free(void *);

void rust_tree_sitter_free(void *p) {
  free(p);
}

#endif
