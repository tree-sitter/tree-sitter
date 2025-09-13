#ifndef TREE_SITTER_WASM_STDINT_H_
#define TREE_SITTER_WASM_STDINT_H_

// https://github.com/llvm/llvm-project/blob/0c3cf200f5b918fb5c1114e9f1764c2d54d1779b/clang/test/Preprocessor/init.c#L1672

typedef signed char int8_t;

typedef short int16_t;

typedef int int32_t;

typedef long long int int64_t;

typedef unsigned char uint8_t;

typedef unsigned short uint16_t;

typedef unsigned int uint32_t;

typedef long long unsigned int uint64_t;

typedef long unsigned int size_t;

typedef long unsigned int uintptr_t;

#define UINT16_MAX 65535

#define UINT32_MAX 4294967295U

#if defined(__wasm32__)

#define SIZE_MAX 4294967295UL

#elif defined(__wasm64__)

#define SIZE_MAX 18446744073709551615UL

#endif

#endif // TREE_SITTER_WASM_STDINT_H_
