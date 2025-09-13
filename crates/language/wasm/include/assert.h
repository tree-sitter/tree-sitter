#ifndef TREE_SITTER_WASM_ASSERT_H_
#define TREE_SITTER_WASM_ASSERT_H_

#ifdef NDEBUG
#define assert(e) ((void)0)
#else
__attribute__((noreturn)) void __assert_fail(const char *assertion, const char *file, unsigned line, const char *function) {
    __builtin_trap();
}
#define assert(expression) \
  ((expression) ? (void)0 : __assert_fail(#expression, __FILE__, __LINE__, __func__))
#endif

#endif // TREE_SITTER_WASM_ASSERT_H_
