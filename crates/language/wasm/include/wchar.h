#ifndef TREE_SITTER_WASM_WCHAR_H_
#define TREE_SITTER_WASM_WCHAR_H_

#include <stdint.h>

typedef __WCHAR_TYPE__ wchar_t;

wchar_t *wcschr(const wchar_t *str, wchar_t c);

size_t wcslen(const wchar_t *str);

#endif // TREE_SITTER_WASM_WCHAR_H_
