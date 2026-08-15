#ifndef TREE_SITTER_WASM_WCTYPE_H_
#define TREE_SITTER_WASM_WCTYPE_H_

typedef unsigned int wint_t;
typedef void *locale_t;

#ifndef weak_alias
#define weak_alias(old, new) \
  extern __typeof(old) new __attribute__((__weak__, __alias__(#old)))
#endif

#if defined(TREE_SITTER_WASM_STDLIB) && !defined(TS_WASM_EXPORT)
#define TS_WASM_EXPORT(name) __attribute__((visibility("default"), export_name(name)))
#elif !defined(TS_WASM_EXPORT)
#define TS_WASM_EXPORT(name)
#endif

TS_WASM_EXPORT("iswalnum") int iswalnum(wint_t wch);

TS_WASM_EXPORT("iswalpha") int iswalpha(wint_t wch);

TS_WASM_EXPORT("iswblank") int iswblank(wint_t wch);

TS_WASM_EXPORT("iswdigit") int iswdigit(wint_t wch);

TS_WASM_EXPORT("iswlower") int iswlower(wint_t wch);

TS_WASM_EXPORT("iswpunct") int iswpunct(wint_t wch);

TS_WASM_EXPORT("iswspace") int iswspace(wint_t wch);

TS_WASM_EXPORT("iswupper") int iswupper(wint_t wch);

TS_WASM_EXPORT("iswxdigit") int iswxdigit(wint_t wch);

TS_WASM_EXPORT("towlower") wint_t towlower(wint_t wch);

TS_WASM_EXPORT("towupper") wint_t towupper(wint_t wch);

#endif // TREE_SITTER_WASM_WCTYPE_H_
