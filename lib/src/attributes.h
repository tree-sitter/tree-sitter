#ifndef TREE_SITTER_ATTRIBUTES_H_
#define TREE_SITTER_ATTRIBUTES_H_

#if defined(__GNUC__) || defined(__clang__)
#define TS_COLD __attribute__((cold, noinline))
#define TS_NOINLINE __attribute__((noinline))
#define TS_PRINTF(format_index, first_argument_index) \
  __attribute__((format(printf, format_index, first_argument_index)))
#define TS_UNLIKELY(x) __builtin_expect(!!(x), 0)
#elif defined(_MSC_VER)
#define TS_COLD __declspec(noinline)
#define TS_NOINLINE __declspec(noinline)
#define TS_PRINTF(format_index, first_argument_index)
#define TS_UNLIKELY(x) (x)
#else
#define TS_COLD
#define TS_NOINLINE
#define TS_PRINTF(format_index, first_argument_index)
#define TS_UNLIKELY(x) (x)
#endif

#endif // TREE_SITTER_ATTRIBUTES_H_
