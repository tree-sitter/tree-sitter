#ifndef TREE_SITTER_WASM_WCTYPE_H_
#define TREE_SITTER_WASM_WCTYPE_H_

typedef int wint_t;

static inline bool iswalpha(wint_t wch) {
  switch (wch) {
  case L'a':
  case L'b':
  case L'c':
  case L'd':
  case L'e':
  case L'f':
  case L'g':
  case L'h':
  case L'i':
  case L'j':
  case L'k':
  case L'l':
  case L'm':
  case L'n':
  case L'o':
  case L'p':
  case L'q':
  case L'r':
  case L's':
  case L't':
  case L'u':
  case L'v':
  case L'w':
  case L'x':
  case L'y':
  case L'z':
  case L'A':
  case L'B':
  case L'C':
  case L'D':
  case L'E':
  case L'F':
  case L'G':
  case L'H':
  case L'I':
  case L'J':
  case L'K':
  case L'L':
  case L'M':
  case L'N':
  case L'O':
  case L'P':
  case L'Q':
  case L'R':
  case L'S':
  case L'T':
  case L'U':
  case L'V':
  case L'W':
  case L'X':
  case L'Y':
  case L'Z':
    return true;
  default:
    return false;
  }
}

static inline bool iswdigit(wint_t wch) {
  switch (wch) {
  case L'0':
  case L'1':
  case L'2':
  case L'3':
  case L'4':
  case L'5':
  case L'6':
  case L'7':
  case L'8':
  case L'9':
    return true;
  default:
    return false;
  }
}

static inline bool iswalnum(wint_t wch) {
  switch (wch) {
  case L'a':
  case L'b':
  case L'c':
  case L'd':
  case L'e':
  case L'f':
  case L'g':
  case L'h':
  case L'i':
  case L'j':
  case L'k':
  case L'l':
  case L'm':
  case L'n':
  case L'o':
  case L'p':
  case L'q':
  case L'r':
  case L's':
  case L't':
  case L'u':
  case L'v':
  case L'w':
  case L'x':
  case L'y':
  case L'z':
  case L'A':
  case L'B':
  case L'C':
  case L'D':
  case L'E':
  case L'F':
  case L'G':
  case L'H':
  case L'I':
  case L'J':
  case L'K':
  case L'L':
  case L'M':
  case L'N':
  case L'O':
  case L'P':
  case L'Q':
  case L'R':
  case L'S':
  case L'T':
  case L'U':
  case L'V':
  case L'W':
  case L'X':
  case L'Y':
  case L'Z':
  case L'0':
  case L'1':
  case L'2':
  case L'3':
  case L'4':
  case L'5':
  case L'6':
  case L'7':
  case L'8':
  case L'9':
    return true;
  default:
    return false;
  }
}

static inline bool iswspace(wint_t wch) {
  switch (wch) {
  case L' ':
  case L'\t':
  case L'\n':
  case L'\v':
  case L'\f':
  case L'\r':
    return true;
  default:
    return false;
  }
}

#endif // TREE_SITTER_WASM_WCTYPE_H_
